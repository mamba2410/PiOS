#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <mmio/interrupt_values.h>

extern void mask_irq();
extern void unmask_irq();

void handle_irq();
void show_invalid_entry_message(uint64_t, uint64_t, uint64_t);

#endif /* INTERRUPTS_H */
