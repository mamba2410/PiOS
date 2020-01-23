// TODO MOVE ME
#define CPU_CONTEXT_OFFSET 0			// cpu_context is the first member if task_t

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
	ret									// Return to the next task's program counter (x30)

