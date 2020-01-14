#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <mmio/interrupt_values.h>
#include <stdint.h>

extern void interrupt_vector_table_init();
extern void mask_irq();
extern void unmask_irq();

void handle_irq_el1h();
void show_invalid_entry_message(uint8_t exception_type, uint64_t esr, uint64_t *elr);
void enable_interrupt_controller();

#endif /* INTERRUPTS_H */
