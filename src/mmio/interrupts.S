#include <mmio/interrupt_values.h>

	.macro vector_table_entry	vector_label	// Define a macro to handle adding vector entries
	.align	7					// Vectors need to be offset 0x80 from each other
	b		\vector_label		// Immediately branch to new location since we only have 0x80 bytes of code to play with here
	.endm						// End the macro

	.macro handle_invalid_entry	type			// Macro to handle interrupts we don't care about. Using macros to leave registers untouched
	save_registers								// Macro to save the processor state
	mov		x0, #\type							// Prepare arguments for the function call
	mrs		x2, esr_el1							//
	mrs		x3, elr_el1							//
	bl		show_invalid_entry_message			// Call the function to display the error
	b		error_hang							// Hang the processor
	.endm										// End the macro

	.macro save_registers						// Save the registers before handling an interrupt
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
	stp		x28, x29, [sp, #0x10 * 14]
	str		x30, 	  [sp, #0x10 * 15]			// Do this for all general putpose registers. Add more as needed
	.endm

	.macro populate_registers					// Repopulate registers after handling an interrupt
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
	ldr		x30, 	  [sp, #0x10 * 15]			// Do this for all general putpose registers. Add more as needed
	add		sp, sp, #REGISTER_FRAME_SIZE		// Move the stack pointer back up
	eret										// Exception return from the handling
	.endm


// Exception vector table, all vectors must be 0x80 bytes apart and must not be larger than 0x80 bytes
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

	vector_table_entry	snc_invalid_el0_32		// Synchronous interrupt at el0 32-bit, invalid (for now)
	vector_table_entry	irq_invalid_el0_32		// Normal interrupt at el0 32-bit, invalid (for now)
	vector_table_entry	fiq_invalid_el0_32		// Fast interrupt at el0 32-bit, invalid
	vector_table_entry	err_invalid_el0_32		// Error interrupt at el0 32-bit, invalid (for now)

	vector_table_entry	snc_invalid_el0_64		// Synchronous interrupt at el0 64-bit, invalid (for now)
	vector_table_entry	irq_invalid_el0_64		// Normal interrupt at el0 64-bit, invalid (for now)
	vector_table_entry	fiq_invalid_el0_64		// Fast interrupt at el0 64-bit, invalid
	vector_table_entry	err_invalid_el0_64		// Error interrupt at el0 64-bit, invalid (for now)

// Mask IRQs for all(?) exception levels
// DAIF - Debug Asynchronous aborts (SError) Irq Fiq
.global mask_irq
mask_irq:
	msr		daifset, #2
	ret

// Unmask TRQs for all(?) exception levels
.global unmask_irq
unmask_irq:
	msr		daifclr, #2
	ret

.global irq_vector_init
irq_vector_init:				// Initialise the vector table
	adr 	x0, vector_table	// Get the vector table address
	msr		vbar_el1, x0		// Put the address in the vector base address register
	ret							// Return

// Functions to handle the vectors
// Valid exceptions

irq_valid_el1h:				// Normal interrupt at EL1h
	save_registers			// Save the current registers to the stack
	bl		handle_irq_el1h	// Branch with link to a C function
	populate_registers		// Repopulate the registers and exception return

// Invalid exceptions, just call the macro
snc_invalid_el1t:
	handle_invalid_entry	SNC_INVALID_EL1T

irq_invalid_el1t:
	handle_invalid_entry	IRQ_INVALID_EL1T

fiq_invalid_el1t:
	handle_invalid_entry	FIQ_INVALID_EL1T

err_invalid_el1t:
	handle_invalid_entry	ERR_INVALID_EL1T


snc_invalid_el1h:
	handle_invalid_entry	SNC_INVALID_EL1H

fiq_invalid_el1h:
	handle_invalid_entry	FIQ_INVALID_EL1H

err_invalid_el1h:
	handle_invalid_entry	ERR_INVALID_EL1H


snc_invalid_el0_32:
	handle_invalid_entry	SNC_INVALID_EL0_32

irq_invalid_el0_32:
	handle_invalid_entry	IRQ_INVALID_EL0_32

fiq_invalid_el0_32:
	handle_invalid_entry	FIQ_INVALID_EL0_32

err_invalid_el0_32:
	handle_invalid_entry	ERR_INVALID_EL0_32


snc_invalid_el0_64:
	handle_invalid_entry	SNC_INVALID_EL0_64

irq_invalid_el0_64:
	handle_invalid_entry	IRQ_INVALID_EL0_64

fiq_invalid_el0_64:
	handle_invalid_entry	FIQ_INVALID_EL0_64

err_invalid_el0_64:
	handle_invalid_entry	ERR_INVALID_EL0_64


// Hang the processor
error_hang:
	nop
	b		error_hang

