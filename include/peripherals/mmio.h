#ifndef MMIO_H
#define MMIO_H

#include <stdint.h>

extern void 	mmio_delay(uint64_t);				// Delay for a number of loops
extern void 	mmio_put32(uint64_t, uint32_t);		// Put 32-bit value into an address
extern uint32_t mmio_get32(uint64_t);				// Get 32-bit value from an address
extern void		delay_millis(uint64_t);

//#define mmio_put32(a, d)	((*a) = (d))			// Faster version of the assembly function definitions
//#define mmio_get32(a) 	((uint32_t)(*a))		// 

#endif /* MMIO_H */
