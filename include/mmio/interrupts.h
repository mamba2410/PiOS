#ifndef INTERRUPTS_H
#define INTERRUPTS_H


#define SNC_INVALID_EL1T	0x0
#define IRQ_INVALID_EL1T	0x1
#define FIQ_INVALID_EL1T	0x2
#define ERR_INVALID_EL1T	0x3
#define SNC_INVALID_EL1H	0x4
#define IRQ_VALID_EL1H		0x5
#define FIQ_INVALID_EL1H	0x6
#define ERR_INVALID_EL1H	0x7
#define SNC_INVALID_EL0_32	0x8
#define IRQ_INVALID_EL0_32	0x9
#define FIQ_INVALID_EL0_32	0xA
#define ERR_INVALID_EL0_32	0xB
#define SNC_INVALID_EL0_64	0xC
#define IRQ_INVALID_EL0_64	0xD
#define FIQ_INVALID_EL0_64	0xE
#define ERR_INVALID_EL0_64	0xF

#define REGISTER_FRAME_SIZE 0x100

#define EMPTY_IRQ			0x0
#define SYSTEM_TIMER_IRQ_0	(1 << 0)
#define SYSTEM_TIMER_IRQ_1	(1 << 1)
#define SYSTEM_TIMER_IRQ_2	(1 << 2)
#define SYSTEM_TIMER_IRQ_3	(1 << 3)


#ifndef __ASSEMBLER__

#include <stdint.h>
extern void interrupt_vector_table_init();
extern void mask_irq();
extern void unmask_irq();

void handle_irq_el1h();
void show_invalid_entry_message(uint8_t exception_type, uint64_t esr, uint64_t *elr);
void enable_interrupt_controller();

extern char* const IRQ_NAMES[16];


#endif /* __ASSEMBLER__ */

#endif /* INTERRUPTS_H */
