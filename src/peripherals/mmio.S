
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

.global delay_millis
delay_millis:					// Delay x0 milliseconds
	mrs		x1, cntfrq_el0		// Get the ARM counter frequency
	mul		x1, x1, x0			// Multiply frequency by ms
	mov		x2, #1000			// Load 1000 into a register
	udiv	x1, x1, x2			// Divide by 1000 to get count
	mrs		x0, cntpct_el0		// Check current timer value
	add		x1, x1, x0			// Add the count wait
1:
	mrs		x0, cntpct_el0		// Check current timer value again
	cmp		x0, x1				// Compare the value and end value
	b.lt	1b					// If we are not there yet, check again
	ret							// If we are, return
