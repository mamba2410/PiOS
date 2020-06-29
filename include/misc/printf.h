#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>

/*
 * User config
 */
#define NEWLINE_CARRIAGE_RETURN		// Should printf add a carriage return to newlines?
#define PRINTF_UART0				// printf uses full uart device
//#define PRINTF_MINI_UART			// printf uses mini uart device

/*
 * C stuff
 */
void	_format		(char *format, va_list va, void(*putc)(char));
void	printf		(char *format, ...);
void	sprintf		(char *str, char *format, ...);

#endif /* PRINTF_H */
