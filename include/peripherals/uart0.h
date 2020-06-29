#ifndef UART0_H
#define UART0_H

/*
 *	Interrupt and register values for PL011 UART
 *	page 175 of bcm2837 peripherals manual
 */

#define IMSC_TXIM			(1<<5)
#define IMSC_RXIM			(1<<4)
#define IMSC_MASK_ALL		(0x7f2)

#define LCRH_VALUE			((1<<4)|(3<<5))			// Enable FIFO, 8-bit word length
#define  ICR_VALUE			(IMSC_MASK_ALL)			// Interrupt clear register, clear all
#define IMSC_VALUE			(IMSC_RXIM)				// Interrupt mask set/clear, allow RX interrupts
#define   CR_VALUE			((1<<0)|(1<<8)|(1<<9))	// Enable UART, RX and TX

/*
 *	UART0 flags register values
 */
#define UART0_FR_BUSY		(1<<3)					// UART busy transmitting data
#define UART0_FR_RXFE		(1<<4)					// Set when RX FIFO empty
#define UART0_FR_TXFF		(1<<5)					// Set when TX FIFO full
#define UART0_FR_RXFF		(1<<6)					// Set when RX FIFI full
#define UART0_FR_TXFE		(1<<7)					// Set when TX FIFO empty

/*
 *	Note on IMSC: Setting the mask bit as high ENABLES the interrupt
 */


void  uart0_init();			// Initialise uart0

void  uart0_putc(char);		// Put character onto uart0
char  uart0_getc();			// Get character from uart0

void  uart0_puts(char *);	// Put string onto uart0
char *uart0_gets();			// Get string from uart0

void  uart0_irq();			// Function called on uart0 IRQ

#endif /* UART0_H */
