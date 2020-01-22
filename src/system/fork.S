.global ret_from_fork
ret_from_fork:
	bl		preempt_enable	// Enable preemption
	mov		x0, x20			// Put the function argument into x0
	blr		x19				// Branch to function pointed to by x19
	// Should never return
