#include <proc/tasks.h>

.global cpu_switch_task
cpu_switch_task:
	mov		x10, #CPU_CONTEXT_OFFSET	// Get the offset in memory for the cpu_context struct
	add		x8, x0, x10					// x8 = prev + offset
	mov		x9, sp						// x9 = prev->cpu_context sp
	stp		x19, x20, [x8], #0x10
	stp		x21, x22, [x8], #0x10
	stp		x23, x24, [x8], #0x10
	stp		x25, x26, [x8], #0x10
	stp		x27, x28, [x8], #0x10
	stp		x29, x30, [x8], #0x10		
	str		x9, [x8]					// Store registers in prev->cpu_context
	add		x8, x1, x10					// x8 = next + offset
	ldp		x19, x20, [x8], #0x10		
	ldp		x21, x22, [x8], #0x10
	ldp		x23, x24, [x8], #0x10
	ldp		x25, x26, [x8], #0x10
	ldp		x27, x28, [x8], #0x10
	ldp		x29, x30, [x8], #0x10
	ldr		x9, [x8]					// Get registers from next->cpu_context
	mov		sp, x9						// sp = next->spu_context.sp


	mov		x10, #FPSIMD_CONTEXT_OFFSET	// Dp the same for the FP/SIMD registers which are 128 bits wide
	add		x8, x0, x10
	stp		q0, q1, [x8], #0x20
	stp		q2, q3, [x8], #0x20
	stp		q4, q5, [x8], #0x20
	stp		q6, q7, [x8], #0x20
	stp		q8, q9, [x8], #0x20
	stp		q10, q11, [x8], #0x20
	stp		q12, q13, [x8], #0x20
	stp		q14, q15, [x8], #0x20
	stp		q16, q17, [x8], #0x20
	stp		q18, q19, [x8], #0x20
	stp		q20, q21, [x8], #0x20
	stp		q22, q23, [x8], #0x20
	stp		q24, q25, [x8], #0x20
	stp		q26, q27, [x8], #0x20
	stp		q28, q29, [x8], #0x20
	stp		q30, q31, [x8], #0x20
	mrs		x11, fpsr				// Save the fp status register
	str		x11, [x8], #8 
	mrs		x11, fpcr				// and control register
	str		x11, [x8] 

	add		x8, x1, x10
	ldp		q0, q1, [x8], #0x20
	ldp		q2, q3, [x8], #0x20
	ldp		q4, q5, [x8], #0x20
	ldp		q6, q7, [x8], #0x20
	ldp		q8, q9, [x8], #0x20
	ldp		q10, q11, [x8], #0x20
	ldp		q12, q13, [x8], #0x20
	ldp		q14, q15, [x8], #0x20
	ldp		q16, q17, [x8], #0x20
	ldp		q18, q19, [x8], #0x20
	ldp		q20, q21, [x8], #0x20
	ldp		q22, q23, [x8], #0x20
	ldp		q24, q25, [x8], #0x20
	ldp		q26, q27, [x8], #0x20
	ldp		q28, q29, [x8], #0x20
	ldp		q30, q31, [x8], #0x20
	ldr		x11, [x8], #8
	msr		fpsr, x11
	ldr		x11, [x8]
	msr		fpcr, x11

	ret									// Return to the next task's program counter (x30)
	

