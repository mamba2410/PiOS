#include <stdint.h>
#include <addresses/gpio.h>
#include <addresses/uart0.h>
#include <peripherals/mailbox.h>
#include <peripherals/mmio.h>
#include <peripherals/baud_rate.h>
#include <peripherals/uart0.h>

/*
 * Initialise the uart0 line
 */
void uart0_init(){
	uint32_t selector;
	uint32_t bitmask;
	mailbox_t mbox;

	mmio_put32(UART0_CR, 0);			// Disable uart0

	// Set clock rate
	mbox.tag_id			= MBOX_TAG_SETCLKR;		// Tag to set clock rate
	mbox.value_size		= 12;					// Value payload is 12 bytes
	mbox.tag_rr			= MBOX_TAG_REQUEST;		// We are requesting
	mbox.value_u32[0]	= UART0_CLOCK_ID;		// Specify the UART clock
	mbox.value_u32[1]	= UART0_CLOCK_RATE;		// Specify the clock rate
	mbox.value_u32[2]	= 0;					// No turbo
	mailbox_send(&mbox, MBOX_CH_PROP);			// Send this mailbox

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

	mmio_put32(UART0_IBRD, 1);			// Hardcoded to 115200 @ 3MHz
	mmio_put32(UART0_FBRD, 40);

	mmio_put32(UART0_LCRH, LCRH_VALUE);	// Enable FIFO and 8 bit words, no parity
	mmio_put32(UART0_IMSC, IMSC_VALUE);	// Mask/enable interrupts
	mmio_put32(UART0_ICR, IMSC_MASK_ALL);	// Clear pending interrupts
	mmio_put32(UART0_CR, CR_VALUE);		// Enable uart0 and rx/tx parts of uart
}

/*
 * Put character on the uart0 line
 */
void uart0_putc(char c){
	while( mmio_get32(UART0_FR) & UART0_FR_TXFF );	// Wait while tx fifo is full
	mmio_put32(UART0_DR, c);						// Put char into fifo when not full
}

/*
 * Get a character from the uart0 line
 */
char uart0_getc(){
	while( mmio_get32(UART0_FR) & UART0_FR_RXFE );	// Wait while rx fifo is empty
	return mmio_get32(UART0_DR);					// read char from fifo when not empty
}

/*
 * Put a string on the uart0 line
 */
void uart0_puts(char *s){
	for(int i = 0; s[i] != '\0'; i++)			// For each non-null character
		uart0_putc(s[i]);						// Put the character onto the uart
}

void uart0_irq(){
	uint8_t i;

	/*
	 *	Handle receive interrupts
	 */
	char buf[9];
	for(i = 0; !( mmio_get32(UART0_FR) & UART0_FR_RXFE ); i++){	// While rx fifo not empty
		buf[i] = uart0_getc();									// Put data in buffer
		uart0_putc(buf[i]);										// For now, echo right back
	}	// FIFO is saved in `buf` with length `i`
}

/*
 * Get a string from the uart0 line
 */
//char *uart0_gets(){}
