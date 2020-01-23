#ifndef MINI_UART_H
#define MINI_UART_H

void	mini_uart_init();			// Initialise mini uart

void	mini_uart_putc(char);		// Put a character to the mini uart
char	mini_uart_getc();			// Get a character from the mini uart

void	mini_uart_puts(char*);		// Put a string to the mini uart
char*	mini_uart_gets();			// Get a string from the mini uart

#endif /* MINI_UART_H */
