#ifndef MMIO_H
#define MMIO_H

#include <stdint.h>

#define MMIO_BASE 0x3F000000

extern void 	mmio_delay(uint64_t);			// Delay for a number of loops
extern void 	mmio_put32(uint64_t, uint32_t);	// Put 32-bit value into an address
extern uint32_t mmio_get32(uint64_t);			// Get 32-bit value from an address

//#define mmio_put32(a, d)	(*( (volatile uint64_t*)(a) ) = d)	// Faster version of the assembly function definitions
//#define mmio_get32(a) 		((uint32_t)(*( (volatile uint64_t*)(a) )))		// 

#endif
