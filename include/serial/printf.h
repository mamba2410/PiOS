#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>

#define NEWLINE_CARRIAGE_RETURN		// Should printf add a carriage return to newlines?

// Set a macro for the putc function printf uses
//#define  uart_init uart0_init
//#define  uart_putc uart0_putc
//#define  uart_getc uart0_getc
//#include <serial/uart0.h>
#define  uart_init mini_uart_init
#define  uart_putc mini_uart_putc
#define  uart_getc mini_uart_getc
#include <serial/mini_uart.h>

void	uart_format (char *format, va_list va);
void	uart_printf (char *format, ...);
//void 	mini_uart_sprintf(char *string, char *format, ...);

#define printf  uart_printf
//#define sprintf mini_uart_sprintf

#endif /* PRINTF_H */
