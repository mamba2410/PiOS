#ifndef DELAY_H
#define DELAY_H

#define DELAY_CYCLES_COUNT	10	// Number of cycles the delay function lasts

#ifndef __ASSEMBLER__
#include <stdint.h>

extern void delay_cycles(uint32_t);

void delay_micros(uint32_t);
void delay_millis(uint32_t);

#endif /* __ASSEMBLER__ */

#endif /* DELAY_H */
