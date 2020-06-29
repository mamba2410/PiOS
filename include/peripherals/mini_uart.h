#ifndef MINI_UART_H
#define MINI_UART_H

#define AUX_IRQ_IP_MASK		(1<<0)		// Bit 0 is set if mini uart has interrupt pending

#define AUX_MU_IER_ENABLE	(0b11<<2)	// Enable interrupts
#define AUX_MU_IER_TX_EN	(1<<1)		// Enable transmit interrupts
#define AUX_MU_IER_RX_EN	(1<<0)		// Enable receive interrupts
#define AUX_MU_IER_VALUE	( AUX_MU_IER_ENABLE | AUX_MU_IER_RX_EN )

#define AUX_ENABLES_VALUE	(1<<0)		// Mini UART, no SPI

#define AUX_MU_IIR_TX		(0b01<<1)	// See page 13 of bcm2835 manual
#define AUX_MU_IIR_RX		(0b10<<1)	// 
#define AUX_MU_IIR_IP		(1<<0)		// Bit clear if interrupt pending

#define AUX_MU_LCR_7BIT		(0b00<<0)	// Enable 7-bit mode
#define AUX_MU_LCR_8BIT		(0b11<<0)	// Enable 8-bit mode
#define AUX_MU_LCR_DLAB		(1<<7)		// Allow DLAB access, must be 0 in operation

#define AUX_MU_MCR_RTS		(1<<1)		// If set, RTS line is low
#define AUX_MU_MCR_VALUE	0			// Don't want it set cause we are ready to send

#define AUX_MU_LSR_TXI		(1<<6)		// If set, TX FIFO empty, transmitter idle
#define AUX_MU_LSR_TXE		(1<<5)		// If set, TX FIFO can accept >=1 bytes
#define AUX_MU_LSR_RO		(1<<1)		// If set, RX FIFO is full and overflowed
#define AUX_MU_LSR_DR		(1<<0)		// If set, RX FIFO has at least 1 byte

										// For bits about CTS and auto flow, see page 13 of bcm2837 peripherals manual
#define AUX_MU_CNTL_TXE		(1<<1)		// Enable transmitter
#define AUX_MU_CNTL_RXE		(1<<0)		// Enable receiver
#define AUX_MU_CNTL_VALUE	(AUX_MU_CNTL_TXE|AUX_MU_CNTL_RXE)	// Enable RX and TX

#ifndef __ASSEMBLER__
void	mini_uart_init();			// Initialise mini uart

void	mini_uart_putc(char);		// Put a character to the mini uart
char	mini_uart_getc();			// Get a character from the mini uart

void	mini_uart_puts(char*);		// Put a string to the mini uart
char*	mini_uart_gets();			// Get a string from the mini uart

void	mini_uart_irq();

#endif

#endif /* MINI_UART_H */
