#ifndef UART0_H
#define UART0_H

void  uart0_init();			// Initialise uart0

void  uart0_putc(char);		// Put character onto uart0
char  uart0_getc();			// Get character from uart0

void  uart0_puts(char *);	// Put string onto uart0
char *uart0_gets();			// Get string from uart0

#endif /* UART0_H */
