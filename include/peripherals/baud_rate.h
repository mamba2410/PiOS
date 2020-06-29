#ifndef BAUD_RATE_H
#define BAUD_RATE_H

#include <stdint.h>


#define BAUD_RATE			115200		// Chosen baud rate

// Clock frequencies
#define SYS_CLOCK_FREQ		250e6		// System clock is 250MHz
#define UART0_CLOCK			3e6			// UART0 clock is 3MHz


// Mini uart values
#define MINI_UART_REG_VAL	(uint32_t)(SYS_CLOCK_FREQ/(8 * BAUD_RATE) - 1)	// Calculate the register value for the baud rate


// PL011 UART0 values
#define BAUD_RATE_DIVIDER	( (double)UART0_CLOCK/(16.0 * BAUD_RATE) )
#define BAUD_RATE_FRACTION	( (BAUD_RATE_DIVIDER-IBRD_VALUE)*64.0 + 0.5 )

#define IBRD_VALUE			(uint32_t)(BAUD_RATE_DIVIDER)
#define FBRD_VALUE			(uint32_t)(BAUD_RATE_FRACTION)

#endif /* BAUD_RATE_H */
