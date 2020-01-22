#include <memory/mem_values.h>
#include <system/arm_system_registers.h>

// Tells the linker to put everything here in the .text.boot section
.section ".text.boot"

/*
 * Note:	x<n> is a 64-bit register
 *			w<n> is the lower 32-bits of x<n>
 */

/*
 * All processor cores run this code, so need to handle it differently for each one
 * otherwise the code will be run 4 times and the serial registers might mess up
 */
 	//.org	0x80000
.global 	_start
_start:
	mrs		x0, mpidr_el1		// Move processor id from system register to gp register
	and		x0,	x0,	#0xff		// Test the last byte of the processor id and put it in the compare register
	//cbz		x0,	el2_entry		// If processor has id zero, go to master
	cbz		x0, master
	// If processor id is not zero, continue to infinite loop

processor_hang:					// Infi-loop to hang the processors we don't want
	b		processor_hang

el2_entry:
	msr		SPsel, #1			// Want to use SP_EL{1,2}
	mrs		x0, CurrentEL		// Get current exception level
	cmp		x0, #Current_EL_EL2	// Are we EL2?
	b.eq	1f					// If we are equal, branch forward to label 1 (?)
	b		el1_entry			// If we aren't equal then go to el1_entry, nothing more to be done
1:
	ldr		x0, =SCTLR_VALUE_MMU_DISABLED	// Load the system control flags into x0
	msr		sctlr_el2, x0		// Put this value in system control register at EL2
	ldr		x0, =HCR_VALUE		// Load the hypervisor config value
	msr		hcr_el2, x0			// Put this into the hypervisor configuration register
	mrs		x0, cnthctl_el2
	orr		x0, x0, #3			// Enable non-secure EL1 and EL0 to access physical timers
	msr		cnthctl_el2, x0		
	mrs		x0, midr_el1		// Get read-only information about the processor, id, num cores etc
	mrs		x1, mpidr_el1		// These can be read differently at different ELs, mainly for virtualisation 
	msr		vpidr_el2, x0		// Set this at a higher level so that EL1+ will all read the same thing
	msr		vmpidr_el2, x1		// We won't be virtualising so this doesn't matter really
	msr		vttbr_el2, xzr		// Store virtual address translation table base as zero, disabling stage 2 translation
	ldr		x0, =SCTLR_VALUE_MMU_DISABLED
	msr		sctlr_el1, x0		// Set EL1 system control register
	mov		x0, #0x33ff
	msr		cptr_el2, x0		// Disable coprocessors, traps to EL2 (not sure what this does but linux does it)
	mov		x0, SPSR_VALUE		// Load the saved program status register value
	msr		spsr_el2, x0		// Put the spsr value in the register
	adr		x0, el1_entry		// Load the el1_entry address to x0
	msr		elr_el2, x0			// Load the exception link register with the address
	eret						// Change exception level and branch to location in elr_el2

master:							// Master label, branched to by processor we want
	ldr		x0, =SCTLR_VALUE_MMU_DISABLED	// Load the system control flags into x0
	msr		sctlr_el1, x0		// Put this value in system control register
	ldr		x0, =HCR_VALUE		// Load the hypervisor config value
	msr		hcr_el2, x0			// Put this into the hypervisor configuration register
	ldr		x0, =SCR_VALUE		// Load the secure configuration value
	msr		scr_el3, x0			// Put this into the secure configuration register
	ldr		x0, =SPSR_VALUE		// Load the desired program status value
	msr		spsr_el3, x0		// Put into the saved program status register
	adr		x0, el1_entry		// Put address of el1_entry into x0
	msr		elr_el3, x0			// Put this into exception link register
	eret						// Return to where the exception registers say

el1_entry:						// Code to be run after processor enters exception level 1
	adr		x0,	bss_begin		// Load bss_begin address
	adr 	x1,	bss_end			// Load bss_end address
	sub		x1,	x1,	x0			// x1 = bss_size = bss_end - bss_start
	bl		zero_memory			// Branch with link to zero out the memory
	
	mov		sp,	#LOW_MEMORY		// Move stack pointer to the low memory location, 4M should be enough since kernel is tiny
	bl		kernel_main			// Branch to kernel_main, defined in a c file

	b 		processor_hang		// If we return from kernel_main, hang the processor


.global	get_exception_level
get_exception_level:			// Global function to get exception level
	mrs		x0, CurrentEL		// Put current exception level in x0
	lsr		x0, x0, #2			// Logical shift right twice, bits 0 and 1 are reserved and always zero
	ret							// Return from function


