#ifndef MMIO_H
#define MMIO_H

#include <stdint.h>

// Delay for a 64-bit number of clock cycles
extern void 	mmio_delay(uint64_t);
// Put a 32-bit uint into a 64-bit address
extern void 	mmio_put32(uint64_t, uint32_t);
// Get a 32-bit uint from a 64-bit address
extern uint32_t mmio_get32(uint64_t);

#endif
