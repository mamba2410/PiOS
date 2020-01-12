#ifndef MINI_UART_H
#define MINI_UART_H

#include <mmio/gpio.h>

#define AUX_ENABLES     (MMIO_BASE+0x00215004)
#define AUX_MU_IO_REG   (MMIO_BASE+0x00215040)
#define AUX_MU_IER_REG  (MMIO_BASE+0x00215044)
#define AUX_MU_IIR_REG  (MMIO_BASE+0x00215048)
#define AUX_MU_LCR_REG  (MMIO_BASE+0x0021504C)
#define AUX_MU_MCR_REG  (MMIO_BASE+0x00215050)
#define AUX_MU_LSR_REG  (MMIO_BASE+0x00215054)
#define AUX_MU_MSR_REG  (MMIO_BASE+0x00215058)
#define AUX_MU_SCRATCH  (MMIO_BASE+0x0021505C)
#define AUX_MU_CNTL_REG (MMIO_BASE+0x00215060)
#define AUX_MU_STAT_REG (MMIO_BASE+0x00215064)
#define AUX_MU_BAUD_REG (MMIO_BASE+0x00215068)


void	mini_uart_init();			// Initialise mini uart

void	mini_uart_putc(char);		// Put a character to the mini uart
char	mini_uart_getc();			// Get a character from the mini uart

void	mini_uart_puts(char*);		// Put a string to the mini uart
char*	mini_uart_gets();			// Get a string from the mini uart

#endif /* MINI_UART_H */
