#include <serial/uart0.h>
#include <mmio/mmio.h>
#include <stdint.h>
#include <mmio/mailbox.h>

/*
 * Initialise the uart0 line
 */
void uart0_init(){
	uint32_t selector;
	uint32_t bitmask;

	mmio_put32(UART0_CR, 0);			// Disable uart0

	// Set clock rate
	mailbox[0] = 9*4;					// Size of mailbox
	mailbox[1] = MBOX_REQUEST;			// We are requesting something
	mailbox[2] = MBOX_TAG_SETCLK;		// Tag to set a clock rate
	mailbox[3] = 12;
	mailbox[4] = 8;
	mailbox[5] = 2;						// Specify the UART0 clock
	mailbox[6] = UART0_CLOCK;			// Set the clock rate
	mailbox[7] = 0;						// Clear turbo (? not sure what this is)
	mailbox[8] = MBOX_TAG_LAST;			// End the mailbox
	mailbox_call(MBOX_CH_PROP);			// Send the mail


	// Setup pins
	selector = mmio_get32(GPFSEL1);		// Grab GPIO selector
	selector &= ~((7<<12) | (7<<15));	// Clean GPIO 14 and 15
	selector |=  ((4<<12) | (4<<15));	// Set them to alt0
	mmio_put32(GPFSEL1, selector);		// Put selector back
				
	mmio_put32(GPPUD, 0);				// Set pull up/down to none (floating)
	mmio_delay(150);					// Delay 150 clock cycles
	bitmask = (1<<14)|(1<<15);			// Set bitmask to pins 14 and 15
	mmio_put32(GPPUDCLK0, bitmask);		// Pulse pins 14 and 15
	mmio_delay(150);					// Delay 150 clock cycles
	mmio_put32(GPPUDCLK0, 0);			// End pulse


	mmio_put32(UART0_ICR, ICR_VALUE);	// Clear pending interrupts

	mmio_put32(UART0_IBRD, 1);			// Hardcoded to 115200 @ 3MHz
	mmio_put32(UART0_FBRD, 40);

	mmio_put32(UART0_LCRH, LCRH_VALUE);	// Enable FIFO and 8 bit words, no parity
	mmio_put32(UART0_IMSC, IMSC_VALUE);	// Mask all interrupts
	mmio_put32(UART0_CR, CR_VALUE);		// Enable uart0 and rx/tx parts of uart
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
