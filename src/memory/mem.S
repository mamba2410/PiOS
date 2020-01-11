
.global zero_memory
zero_memory:					// Zero out memory section, start at x0 for x1 bytes
	str		xzr, [x0], #8		// Fill address at x0 with the zero register (64 bits of 0) and increment address by 8 bytes
	subs	x1,	x1,	#8			// Decrement the size by 8
	b.gt	zero_memory			// If size is positive, do it again
	ret							// Return to function call
