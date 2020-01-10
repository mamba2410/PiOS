
// Let anything use this function
.global mmio_put32
mmio_put32:
	// Put the last(?) 32 bits of register 1
	// into address pointed to by x0
	str	w1,	[x0]
	// Return to where you came from
	ret


// Let anything use this function
.global mmio_get32
mmio_get32:
	// Put last(?) 32 bits of data at [x0]
	// Into w0
	ldr	w0,	[x0]
	// Go back to where you came
	ret

// Let anything use this function
.global mmio_delay
mmio_delay:
	// decrements count by 1
	subs	x0,	x0,	#1
	// if not zero, do it again
	bne		mmio_delay
	// Go back to call point
	ret

