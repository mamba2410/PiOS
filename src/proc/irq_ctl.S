/*
 * Functions for interrupt control
 */

.global mask_irq
mask_irq:					// Mask IRQs for all exception levels 
	msr		daifset, #2		// DAIF - Debug Asynchronous Irq Frq
	ret

.global unmask_irq
unmask_irq:					// Unmask IRQs for all exception levels
	msr		daifclr, #2
	ret

