#include <memory/mem.h>
#include <sysregs.h>

.section ".text.boot"			// Put all of this in .text.boot

/*
 * All processor cores run this code, so need to handle it differently for each one
 * otherwise the code will be run 4 times and the serial registers might mess up
 */
//.org	0x80000					// This code is running at 0x80000 (or 0x00000 if kernel_old is enabled in config.txt)
.global 	_start
_start:
	mrs		x0, mpidr_el1		// Move processor id from system register to gp register
	and		x0,	x0,	#0xff		// Test the last byte of the processor id and put it in the compare register
	cbz		x0, 1f				// Are we ID zero? if so go 1 forward	

processor_hang:					// If not, infi-loop
	b processor_hang			//

1:
	mrs		x0, CurrentEL		// Get the current EL
	cmp		x0, #Current_EL_EL1	// Are we EL1?
	b.eq	el1_entry			// If so, go to el1_entry
	cmp		x0, #Current_EL_EL2	// Are we EL2?
	b.eq	el2_entry			// If so, go to el2_entry
								// If not, we must be EL3 (or EL0, but meh)

el3_entry:
	ldr		x0, =SCR_VALUE		// Load the secure configuration value
	msr		scr_el3, x0			// Put this into the secure configuration register
	ldr		x0, =SPSR_EL3_VALUE	// We want to mask all and go to EL2h
	msr		spsr_el3, x0		// Put that in the right register
	adr		x0, el2_entry		// Load address of el2_entry
	msr		elr_el3, x0			// Exception link is now el2_entry
	eret						// Exception return, become EL2h and go to el2_entry

el2_entry:
	msr		SPsel, #1			// Want to use SP_EL{1,2}
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
	mov		x0, #0x33ff
	msr		cptr_el2, x0		// Disable coprocessors, traps to EL2 (not sure what this does but linux does it)
	ldr		x0, =SPSR_EL2_VALUE	// Load the saved program status register value
	msr		spsr_el2, x0		// Put the spsr value in the register
	adr		x0, el1_entry		// Load the el1_entry address to x0
	msr		elr_el2, x0			// Load the exception link register with the address
	eret						// Change exception level and branch to location in elr_el2

el1_entry:						// Code to be run after processor enters exception level 1
	ldr		x0, =SCTLR_VALUE_MMU_DISABLED
	msr		sctlr_el1, x0
	ldr		x0, =CPACR_VALUE	// Load CPACR value into x0
	msr		cpacr_el1, x0		// Set the CPACR value
	adr		x0,	__bss_start		// Load __bss_start address
	adr 	x1,	__bss_end		// Load __bss_end address
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


