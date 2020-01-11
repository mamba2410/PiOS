#include <serial/uart0.h>
#include <mmio.h>
#include <stdint.h>

/*
 * Initialise the uart0 line
 */
void uart0_init(){
	uint32_t bitmask;
	mmio_put32(UART0_CR, 0);				// Disable uart0
				
	mmio_put32(GPPUD, 0);					// Set pull up/down to none (floating)
	mmio_delay(150);						// Delay 150 clock cycles
	bitmask = (1<<14)|(1<<15);				// Set bitmask to pins 14 and 15
	mmio_put32(GPPUDCLK0, bitmask);			// Pulse pins 14 and 15
	mmio_delay(150);						// Delay 150 clock cycles
	mmio_put32(GPPUDCLK0, 0);				// End pulse

	mmio_put32(UART0_ICR, 0x7FF);			// Clear pending interrupts

	// Write to integer and fractional part of the uart registers
	// Hardcoded at 115200 for now
	mmio_put32(UART0_IBRD, 1);
	mmio_put32(UART0_FBRD, 40);

	bitmask = (1<<4)|(1<<5)|(1<<6);
	mmio_put32(UART0_LCRH, bitmask);	// Enable FIFO and 8 bits with 1 stop bit, no parity
	bitmask = (1<<1)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9)|(1<<10);
	mmio_put32(UART0_IMSC, bitmask);	// Mask all interrupts

	bitmask = (1<<0)|(1<<8)|(1<<9);
	mmio_put32(UART0_CR, bitmask);		// Enable uart0 and rx/tx parts of uart
}

/*
 * Put character on the uart0 line
 */
void uart0_putc(char c){
	while( mmio_get32(UART0_FR) & (1<<5) );		// Wait for flag register to say its okay
	mmio_put32(UART0_DR, c);					// Put the character into the register
}

/*
 * Get a character from the uart0 line
 */
char uart0_getc(){
	while( mmio_get32(UART0_FR) & (1<<4) );		// Wait for flag register to say its okay
	return mmio_get32(UART0_DR);				// Read and return from data register
}

/*
 * Put a string on the uart0 line
 */
void uart0_puts(char *s){
	for(int i = 0; s[i] != '\0'; i++)			// For each non-null character
		uart0_putc(s[i]);						// Put the character onto the uart
}

/*
 * Get a string from the uart0 line
 */
//char *uart0_gets(){}
