
.global mmio_put32
mmio_put32:				// Put 32 bits of data into an address
	str		w1,	[x0]	// Put the lower 32 bits of x1 into the address in x0
	ret					// Return to function call

.global mmio_get32
mmio_get32:				// Get 32 bits of data from an address
	ldr	w0,	[x0]		// Load x0 with the lower 32 bits of data at the address x0
	ret					// Return to function call

.global mmio_delay
mmio_delay:				// Delay x0 clock cycles
	subs	x0,	x0,	#1	// Decrement first argument
	bne		mmio_delay	// If not zero, do it again
	ret					// Return to function call

