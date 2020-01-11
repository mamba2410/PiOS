#ifndef MINI_UART_H
#define MINI_UART_H

#include <serial/gpio.h>

#define AUX_ENABLES     (PERIPHERAL_BASE+0x00215004)
#define AUX_MU_IO_REG   (PERIPHERAL_BASE+0x00215040)
#define AUX_MU_IER_REG  (PERIPHERAL_BASE+0x00215044)
#define AUX_MU_IIR_REG  (PERIPHERAL_BASE+0x00215048)
#define AUX_MU_LCR_REG  (PERIPHERAL_BASE+0x0021504C)
#define AUX_MU_MCR_REG  (PERIPHERAL_BASE+0x00215050)
#define AUX_MU_LSR_REG  (PERIPHERAL_BASE+0x00215054)
#define AUX_MU_MSR_REG  (PERIPHERAL_BASE+0x00215058)
#define AUX_MU_SCRATCH  (PERIPHERAL_BASE+0x0021505C)
#define AUX_MU_CNTL_REG (PERIPHERAL_BASE+0x00215060)
#define AUX_MU_STAT_REG (PERIPHERAL_BASE+0x00215064)
#define AUX_MU_BAUD_REG (PERIPHERAL_BASE+0x00215068)

// Function definitions for initialisation
void	mini_uart_init();

// Function definitions for communication between the mini uart
void	mini_uart_putc(char);
void	mini_uart_puts(char*);

char	mini_uart_getc();
char*	mini_uart_gets();

#endif
