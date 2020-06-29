#ifndef MINI_UART_H
#define MINI_UART_H

#define AUX_IRQ_IP_MASK		(1<<0)		// Bit 0 is set if mini uart has interrupt pending


#define AUX_MU_IER_ENABLE	(0b11<<2)	// Enable interrupts
#define AUX_MU_IER_TX_EN	(1<<1)		// Enable transmit interrupts
#define AUX_MU_IER_RX_EN	(1<<0)		// Enable receive interrupts
#define AUX_MU_IER_REG_VAL	( AUX_MU_IER_ENABLE | AUX_MU_IER_RX_EN )

#ifndef __ASSEMBLER__
void	mini_uart_init();			// Initialise mini uart

void	mini_uart_putc(char);		// Put a character to the mini uart
char	mini_uart_getc();			// Get a character from the mini uart

void	mini_uart_puts(char*);		// Put a string to the mini uart
char*	mini_uart_gets();			// Get a string from the mini uart
#endif

#endif /* MINI_UART_H */
