#ifndef DELAY_H
#define DELAY_H

#ifndef __ASSEMBLER__
#include <stdint.h>

void delay_cycles(uint32_t);

void delay_micros(uint32_t);
void delay_millis(uint32_t);

#endif /* __ASSEMBLER__ */

#endif /* DELAY_H */
