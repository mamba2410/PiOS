#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>

// Set a macro for the putc function printf uses
#define  uart_putc uart0_putc
#include <serial/uart0.h>

void	uart_format (char *format, va_list va);
void	uart_printf (char *format, ...);
//void 	mini_uart_sprintf(char *string, char *format, ...);

#define printf  uart_printf
//#define sprintf mini_uart_sprintf

#endif /* PRINTF_H */
