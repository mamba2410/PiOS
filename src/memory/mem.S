
.global zero_memory
zero_memory:					// Zero out memory section, start at x0 for x1 bytes
	str		xzr, [x0], #8		// Fill address at x0 with the zero register (64 bits of 0) and increment address by 8 bytes
	subs	x1,	x1,	#8			// Decrement the size by 8
	b.gt	zero_memory			// If size is positive, do it again
	ret							// Return to function call

.global memcpy
memcpy:							// Copy x1 bytes into address 
	ldr		x3, [x1], #8		// Load contents of address at x1 into x3 and increment x1 by 8 bytes
	str		x3, [x0], #8		// Store x3 into address at x0
	subs	x2, x2, #8			// Decrease the number of bytes by 8
	b.gt	memcpy				// If we still have bytes to go, loop
	ret							// If not, return
