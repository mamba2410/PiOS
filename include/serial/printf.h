#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>

/*
 * User config
 */
#define NEWLINE_CARRIAGE_RETURN		// Should printf add a carriage return to newlines?
//#define PRINTF_MINI_UART			// printf uses mini uart device
#define PRINTF_UART0				// printf uses full uart device

/*
 * C stuff
 */
void	uart_format (char *format, va_list va);
void	uart_printf (char *format, ...);

// Quick macro to allow printf() instead of uart_printf()
#define printf  uart_printf

// Set uart0 as the device printf uses
#ifdef PRINTF_UART0
#ifndef PRINTF_MINI_UART
#include <serial/uart0.h>
#define  uart_init uart0_init
#define  uart_putc uart0_putc
#define  uart_getc uart0_getc
#endif /* PRINTF_MINI_UART */
#endif /* PRINTF_UART0 */

// Set mini uart as the device printf uses
#ifdef PRINTF_MINI_UART
#include <serial/mini_uart.h>
#define  uart_init mini_uart_init
#define  uart_putc mini_uart_putc
#define  uart_getc mini_uart_getc
#endif /* PRINTF_MINI_UART */

#endif /* PRINTF_H */
