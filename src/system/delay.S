#include <addresses/timer.h>
/*
.global delay_cycles
delay_cycles:				// Delay x0 clock cycles
	ldr		w1, TIMER_CLO
	subs	x0,	x0,	#1		// Decrement first argument
	bne		delay_cycles	// If not zero, do it again
	ret						// Return to function call
*/
