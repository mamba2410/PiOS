#include <memory/mem.h>
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
.global 	_start
_start:
	mrs		x0, mpidr_el1		// Move processor id from system register to gp register
	and		x0,	x0,	#0xff		// Test the last byte of the processor id and put it in the compare register
	cbz		x0,	master			// If processor has id zero, go to master
	b		processor_hang		// If processor id is not zero, continue to infinite loop

processor_hang:					// Infi-loop to hang the processors we don't want
	b		processor_hang

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


