#ifndef UART0_H
#define UART0_H

#include <mmio/gpio.h>

#define UART0_BASE		((uint64_t*)(MMIO_BASE + 0x00201000))

#define UART0_DR    	((uint64_t*)(UART0_BASE + 0x00))
#define UART0_RSRECR	((uint64_t*)(UART0_BASE + 0x04))
#define UART0_FR    	((uint64_t*)(UART0_BASE + 0x18))
#define UART0_ILPR  	((uint64_t*)(UART0_BASE + 0x20))
#define UART0_IBRD  	((uint64_t*)(UART0_BASE + 0x24))
#define UART0_FBRD  	((uint64_t*)(UART0_BASE + 0x28))
#define UART0_LCRH  	((uint64_t*)(UART0_BASE + 0x2C))
#define UART0_CR    	((uint64_t*)(UART0_BASE + 0x30))
#define UART0_IFLS  	((uint64_t*)(UART0_BASE + 0x34))
#define UART0_IMSC  	((uint64_t*)(UART0_BASE + 0x38))
#define UART0_RIS   	((uint64_t*)(UART0_BASE + 0x3C))
#define UART0_MIS   	((uint64_t*)(UART0_BASE + 0x40))
#define UART0_ICR   	((uint64_t*)(UART0_BASE + 0x44))
#define UART0_DMACR 	((uint64_t*)(UART0_BASE + 0x48))
#define UART0_ITCR  	((uint64_t*)(UART0_BASE + 0x80))
#define UART0_ITIP  	((uint64_t*)(UART0_BASE + 0x84))
#define UART0_ITOP  	((uint64_t*)(UART0_BASE + 0x88))
#define UART0_TDR   	((uint64_t*)(UART0_BASE + 0x8C))


#define UART0_CLOCK			3e6			// 3MHz
#define BAUD_RATE			115200
#define BAUD_RATE_DIVIDER	( (double)UART0_CLOCK/(16.0 * BAUD_RATE) )
#define BAUD_RATE_FRACTION	( (BAUD_RATE_DIVIDER-IBRD_VALUE)*64.0 + 0.5 )

#define IBRD_VALUE			(uint32_t)(BAUD_RATE_DIVIDER)
#define FBRD_VALUE			(uint32_t)(BAUD_RATE_FRACTION)
#define LCRH_VALUE			((1<<4)|(3<<5))			// Enable FIFO, 8-bit word length
#define  ICR_VALUE			(0x7F2)
#define IMSC_VALUE			(0x7F2)					// Mask all interrupts, some bits are unsupported
#define   CR_VALUE			((1<<0)|(1<<8)|(1<<9))	// Enable UART, RX and TX


void  uart0_init();			// Initialise uart0

void  uart0_putc(char);		// Put character onto uart0
char  uart0_getc();			// Get character from uart0

void  uart0_puts(char *);	// Put string onto uart0
char *uart0_gets();			// Get string from uart0

#endif /* UART0_H */
