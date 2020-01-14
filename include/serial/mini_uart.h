#ifndef MINI_UART_H
#define MINI_UART_H

#include <mmio/gpio.h>
#include <stdint.h>

#define AUX_ENABLES     	((uint64_t*)(MMIO_BASE+0x00215004))
#define AUX_MU_IO_REG   	((uint64_t*)(MMIO_BASE+0x00215040))
#define AUX_MU_IER_REG  	((uint64_t*)(MMIO_BASE+0x00215044))
#define AUX_MU_IIR_REG  	((uint64_t*)(MMIO_BASE+0x00215048))
#define AUX_MU_LCR_REG  	((uint64_t*)(MMIO_BASE+0x0021504C))
#define AUX_MU_MCR_REG  	((uint64_t*)(MMIO_BASE+0x00215050))
#define AUX_MU_LSR_REG  	((uint64_t*)(MMIO_BASE+0x00215054))
#define AUX_MU_MSR_REG  	((uint64_t*)(MMIO_BASE+0x00215058))
#define AUX_MU_SCRATCH  	((uint64_t*)(MMIO_BASE+0x0021505C))
#define AUX_MU_CNTL_REG 	((uint64_t*)(MMIO_BASE+0x00215060))
#define AUX_MU_STAT_REG 	((uint64_t*)(MMIO_BASE+0x00215064))
#define AUX_MU_BAUD_REG 	((uint64_t*)(MMIO_BASE+0x00215068))

// Constants for the baud rate
#define SYS_CLOCK_FREQ		250e6									// System clock frequency is 250MHz
#define BAUD_RATE			115200									// Chosen baud rate
#define BAUD_RATE_REG_VAL	(uint32_t)(SYS_CLOCK_FREQ/(8 * BAUD_RATE) - 1)	// Calculate the register value for the baud rate
//#define BAUD_RATE_REG_VAL	270

void	mini_uart_init();			// Initialise mini uart

void	mini_uart_putc(char);		// Put a character to the mini uart
char	mini_uart_getc();			// Get a character from the mini uart

void	mini_uart_puts(char*);		// Put a string to the mini uart
char*	mini_uart_gets();			// Get a string from the mini uart

#endif /* MINI_UART_H */
