#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>

// TODO implement sprintf
// TODO replace all mini_uart_putc with a macro that user can change

void	mini_uart_printf (char *format, ...);
//void 	mini_uart_sprintf(char *string, char *format, ...);
void	mini_uart_format (char *format, va_list va);

#define printf  mini_uart_printf
//#define sprintf mini_uart_sprintf


#endif /* PRINTF_H */
