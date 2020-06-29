#ifndef INTERRUPTS_H
#define INTERRUPTS_H


#define SNC_INVALID_EL1T	0x00
#define IRQ_INVALID_EL1T	0x01
#define FIQ_INVALID_EL1T	0x02
#define ERR_INVALID_EL1T	0x03
#define SNC_INVALID_EL1H	0x04
#define IRQ_INVALID_EL1H	0x05
#define FIQ_INVALID_EL1H	0x06
#define ERR_INVALID_EL1H	0x07
#define SNC_INVALID_EL0_32	0x08
#define IRQ_INVALID_EL0_32	0x09
#define FIQ_INVALID_EL0_32	0x0A
#define ERR_INVALID_EL0_32	0x0B
#define SNC_INVALID_EL0_64	0x0C
#define IRQ_INVALID_EL0_64	0x0D
#define FIQ_INVALID_EL0_64	0x0E
#define ERR_INVALID_EL0_64	0x0F

#define SNC_ERROR_EL0_64	0x10
#define	SYSCALL_ERROR_EL0_64 0x11

#define REGISTER_FRAME_SIZE 0x110
#define X0_REGISTER_OFFSET	0x0

/*
 *	Values from page 113 of ARM peripherals manual
 */
#define EMPTY_IRQ			0x0
#define SYSTEM_TIMER_IRQ_0	(1 << 0)
#define SYSTEM_TIMER_IRQ_1	(1 << 1)
#define SYSTEM_TIMER_IRQ_2	(1 << 2)
#define SYSTEM_TIMER_IRQ_3	(1 << 3)
#define AUX_IRQ				(1 << 29)
#define UART_IRQ			(1 << (57-32))	// Interrupt 57, inreg 2 so sub 32 to get shift

#define IER_1_VALUE			( SYSTEM_TIMER_IRQ_0 | AUX_IRQ )
#define IER_2_VALUE			( UART_IRQ )

#ifndef __ASSEMBLER__

#include <stdint.h>

extern void interrupt_vector_table_init();

void handle_irq_el1h();
void handle_el0_64_unknown();
void handle_aux_irq();
void handle_uart_irq();
void show_invalid_entry_message(uint8_t exception_type, uint64_t esr, uint64_t elr);
void enable_interrupt_controller();

extern char* const IRQ_NAMES[];


#endif /* __ASSEMBLER__ */

#endif /* INTERRUPTS_H */
