#include <misc/interrupts.h>
#include <misc/syscalls.h>
#include <sysregs.h>

/*
 * ======== handle_invalid_entry ========
 */
	.macro handle_invalid_entry	exception_level,type	// Macro to handle interrupts we don't care about. Using macros to leave registers untouched
	save_registers \exception_level				// Macro to save the processor state
	mov		x0, #\type							// Prepare arguments for the function call
	mrs		x1, esr_el1							//
	mrs		x2, elr_el1							//
	//mov		x2, sp							// debug show current sp
	bl		show_invalid_entry_message			// Call the function to display the error
	b		error_hang							// Hang the processor
	.endm										// End the macro


/*
 * ======== save_registers ========
 */
	.macro save_registers, exception_level		// Save the registers before handling an interrupt
	sub		sp, sp, #REGISTER_FRAME_SIZE		// Move the stack pointer to below the register frame
	stp		x0,  x1,  [sp, #0x10 * 0]			// Store pair(?) of registers to above the stack
	stp		x2,  x3,  [sp, #0x10 * 1]
	stp		x4,  x5,  [sp, #0x10 * 2]
	stp		x6,  x7,  [sp, #0x10 * 3]
	stp		x8,  x9,  [sp, #0x10 * 4]
	stp		x10, x11, [sp, #0x10 * 5]
	stp		x12, x13, [sp, #0x10 * 6]
	stp		x14, x15, [sp, #0x10 * 7]
	stp		x16, x17, [sp, #0x10 * 8]
	stp		x18, x19, [sp, #0x10 * 9]
	stp		x20, x21, [sp, #0x10 * 10]
	stp		x22, x23, [sp, #0x10 * 11]
	stp		x24, x25, [sp, #0x10 * 12]
	stp		x26, x27, [sp, #0x10 * 13]
	stp		x28, x29, [sp, #0x10 * 14]			// Do this for all general purpose registers

	.if		\exception_level==0					// Are we EL0?
	mrs		x21, sp_el0							// If so, store the EL0 stack pointer
	.else										// If we aren't EL0
	add		x21, sp, #REGISTER_FRAME_SIZE		// Store the current stack pointer
	.endif /* \exception_level=0 */				// 
	stp		x30, x21, [sp, #0x10 * 15]			// Store x30, x21 on stack

	mrs		x22, elr_el1						// Get exception link register
	mrs		x23, spsr_el1						// Get program status register
	stp		x22, x23, [sp, #0x10 * 16]			// Save to stack
	.endm
	

/*
 * ======== populate_regisers ========
 */
	.macro populate_registers, exception_level	// Repopulate registers after handling an interrupt
	ldp		x30, x21, [sp, #0x10 * 15]			// Load x30 and sp
	.if \exception_level==0						// Are we EL0?
	msr		sp_el0, x21							// If we are, save the stack pointer
	.endif /* \exception_level==0 */			

	ldp		x22, x23, [sp, #0x10 * 16]			// Load into registers
	msr		elr_el1, x22						// Restore exception link register
	msr		spsr_el1, x23						// Restore program status register

	ldp		x0,  x1,  [sp, #0x10 * 0]			// Load pair(?) of registers to above the stack
	ldp		x2,  x3,  [sp, #0x10 * 1]
	ldp		x4,  x5,  [sp, #0x10 * 2]
	ldp		x6,  x7,  [sp, #0x10 * 3]
	ldp		x8,  x9,  [sp, #0x10 * 4]
	ldp		x10, x11, [sp, #0x10 * 5]
	ldp		x12, x13, [sp, #0x10 * 6]
	ldp		x14, x15, [sp, #0x10 * 7]
	ldp		x16, x17, [sp, #0x10 * 8]
	ldp		x18, x19, [sp, #0x10 * 9]
	ldp		x20, x21, [sp, #0x10 * 10]
	ldp		x22, x23, [sp, #0x10 * 11]
	ldp		x24, x25, [sp, #0x10 * 12]
	ldp		x26, x27, [sp, #0x10 * 13]
	ldp		x28, x29, [sp, #0x10 * 14]
	add		sp, sp, #REGISTER_FRAME_SIZE		// Move the stack pointer back up
	eret
	.endm


/*
 * ======== vector_table_entry ========
 */
	.macro vector_table_entry	vector_label	// Define a macro to handle adding vector entries
	.align	7									// Vectors need to be offset 0x80 from each other
	b		\vector_label						// Immediately branch to new location since we only have 0x80 bytes of code to play with here
	.endm										// End the macro



/*
 * ======== VECTOR TABLE ========
 * Exception vector table, all vectors must be 0x80 bytes apart and must not be larger than 0x80 bytes
 * Labels are not defined in this file, they are defined in the handler file.
 * 
 */
.align 11
.global vector_table
vector_table:
	vector_table_entry	snc_invalid_el1t		// Synchronous interrupt at el1t, invalid (for now)
	vector_table_entry	irq_invalid_el1t		// Normal interrupt at el1t, invalid (for now)
	vector_table_entry	fiq_invalid_el1t		// Fast interrupt at el1t, invalid
	vector_table_entry	err_invalid_el1t		// Error interrupt at el1t, invalid (for now)

	vector_table_entry	snc_invalid_el1h		// Synchronous interrupt at el1h, invalid (for now)
	vector_table_entry	irq_valid_el1h			// Normal interrupt at el1h, valid, will handle it
	vector_table_entry	fiq_invalid_el1h		// Fast interrupt at el1h, invalid
	vector_table_entry	err_invalid_el1h		// Error interrupt at el1h, invalid (for now)

	vector_table_entry	snc_valid_el0_64		// Synchronous interrupt at el0 64-bit, valid
	vector_table_entry	irq_valid_el0_64		// Normal interrupt at el0 64-bit, valid
	vector_table_entry	fiq_invalid_el0_64		// Fast interrupt at el0 64-bit, invalid
	vector_table_entry	err_invalid_el0_64		// Error interrupt at el0 64-bit, invalid (for now)

	vector_table_entry	snc_invalid_el0_32		// Synchronous interrupt at el0 32-bit, invalid (for now)
	vector_table_entry	irq_invalid_el0_32		// Normal interrupt at el0 32-bit, invalid (for now)
	vector_table_entry	fiq_invalid_el0_32		// Fast interrupt at el0 32-bit, invalid
	vector_table_entry	err_invalid_el0_32		// Error interrupt at el0 32-bit, invalid (for now)

/*
 * Set the vector table
 */
.global interrupt_vector_table_init
interrupt_vector_table_init:	// Initialise the vector table
	adr 	x0, vector_table	// Get the vector table address
	msr		vbar_el1, x0		// Put the address in the vector base address register
	ret							// Return




/*
 * ======== EXCEPTION HANDLING ========
 */

// Valid (handled) exceptions

irq_valid_el1h:				// Normal interrupt at EL1h
	save_registers 1		// Save the current registers to the stack at EL1
	bl		handle_irq_el1h	// Branch with link to a C function
	populate_registers 1	// Repopulate the registers at EL1
	eret					// Exception return

irq_valid_el0_64:			// Normal interrupt at EL0 64-bit
	save_registers 0		// Save the current registers to the stack at EL0
	bl		handle_irq_el1h	// Branch with link to a C function
							// Note: Branches to EL1h function since it does exactly the same thing
	populate_registers 0	// Repopulate the registers at EL0
	eret					// Exception return


snc_valid_el0_64:			// Synchronous interrupt at EL0 64-bit
	save_registers 0		// Save registers at EL0
	mrs		x25, esr_el1	// Read exception syndrome register
	lsr		x24, x25, #ESR_ELx_EC_SHIFT			// Load the exceptino class into x24

	cmp		x24, #ESR_ELx_EC_SVC64				// Are we handling an SVC 64-bit interrupt?
	b.eq	el0_64_svc							// If we are, branch to handle that
	cmp		x24, #ESR_ELx_EC_DA_LOW				// Are qwe handling a data abort?
	b.eq	el0_64_da							// If so, brahcn to it

	cmp		x24, #ESR_ELx_EC_UNKNOWN			// Are we handling an unknown/misc exception?
	b.eq	snc_valid_el0_64_unknown			// ...if we are, branch to asm function to handle

	handle_invalid_entry 0, SNC_ERROR_EL0_64	// If nothing matched, throw an error

snc_valid_el0_64_unknown:
	mrs		x0, esr_el1							// arg1 = esr
	mrs		x1, elr_el1							// arg2 = elr
	bl		handle_el0_64_unknown				// Branch to c function
	handle_invalid_entry 0, SNC_ERROR_EL0_64	// If nothing matched, throw an error
	

// Branches used by valid exceptions

el0_64_svc:
	adr		x27, syscall_table		// Load syscall table pointer
	uxtw	x26, w8					// Put syscall number in x8
	mov		x25, #SYSCALL_TOTAL		// Put number of syscalls in x25
	bl		unmask_irq				// Enable IRQs
	cmp		x26, x25				// Are we a valid syscall?
	b.hs	invalid_syscall			// If not, go to invalid syscall

	ldr		x16, [x27, x26, lsl #3]	// Get address of sys_* function
	blr		x16						// Cal the sys_* function
	b ret_from_syscall

el0_64_da:
	bl		unmask_irq				// Allow interrupts
	mrs		x0, far_el1				// Get the fault address register
	mrs		x1, esr_el1				// Get the exception syndrome register
	bl		_mem_abort				// Branch to a C function for the heavy lifting
	cmp		x0, #0					// Was everything ok?
	b.eq	1f						// If so, continue
	handle_invalid_entry 0, DA_ERROR_EL0_64	// If not, yell about it
1:
	bl		mask_irq				// Disable interrupts
	populate_registers 0			// Return from the interrupt
	eret							//

invalid_syscall:
	handle_invalid_entry 0, SYSCALL_ERROR_EL0_64	// Handle invalid exception

ret_from_syscall:							// When returning from a syscall
	bl		mask_irq						// Disable IRQs
	str		x0, [sp, X0_REGISTER_OFFSET]	// Store return value into saved registers
	populate_registers 0					// Populate those registers
	eret									// Exception return back to user mode

// Note: This is here because it needs the populate_registers macro
.global ret_from_fork
ret_from_fork:
	bl		preempt_enable	// Enable preemption
	cbz		x19, ret_to_user// If x19 s zero, we must be in user mode
	mov		x0, x20			// Put the function argument into x0
	blr		x19				// Branch to function pointed to by x19
ret_to_user:
	bl		mask_irq		// Disable IRQs
	populate_registers 0	// Restore registers
	eret					// Exception return


// Invalid (unhandled) exceptions

// EL1t
snc_invalid_el1t:
	handle_invalid_entry	1, SNC_INVALID_EL1T

irq_invalid_el1t:
	handle_invalid_entry	1, IRQ_INVALID_EL1T

fiq_invalid_el1t:
	handle_invalid_entry	1, FIQ_INVALID_EL1T

err_invalid_el1t:
	handle_invalid_entry	1, ERR_INVALID_EL1T


// EL1h (what pios currently runs at)
snc_invalid_el1h:
	handle_invalid_entry	1, SNC_INVALID_EL1H

fiq_invalid_el1h:
	handle_invalid_entry	1, FIQ_INVALID_EL1H

err_invalid_el1h:
	handle_invalid_entry	1, ERR_INVALID_EL1H


// EL0 32-bit mode
snc_invalid_el0_32:
	handle_invalid_entry	0, SNC_INVALID_EL0_32

irq_invalid_el0_32:
	handle_invalid_entry	0, IRQ_INVALID_EL0_32

fiq_invalid_el0_32:
	handle_invalid_entry	0, FIQ_INVALID_EL0_32

err_invalid_el0_32:
	handle_invalid_entry	0, ERR_INVALID_EL0_32


// EL0 64-bit mode
fiq_invalid_el0_64:
	handle_invalid_entry	0, FIQ_INVALID_EL0_64

err_invalid_el0_64:
	handle_invalid_entry	0, ERR_INVALID_EL0_64


// Hang the processor
error_hang:
	nop
	b		error_hang

