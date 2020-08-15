#ifndef ADDR_SYSTEM_TIMER_H
#define ADDR_SYSTEM_TIMER_H

#include <addresses/addr_base.h>

#define SYSTEM_TIMER_BASE		(MMIO_BASE+0x00003000)

#define SYSTEM_TIMER_CS        (SYSTEM_TIMER_BASE+0x00)	// Control/status
#define SYSTEM_TIMER_CLO       (SYSTEM_TIMER_BASE+0x04)	// System timer low 32-bits
#define SYSTEM_TIMER_CHI       (SYSTEM_TIMER_BASE+0x08)	// System timer high 32-bits
#define SYSTEM_TIMER_C0        (SYSTEM_TIMER_BASE+0x0C)
#define SYSTEM_TIMER_C1        (SYSTEM_TIMER_BASE+0x10)
#define SYSTEM_TIMER_C2        (SYSTEM_TIMER_BASE+0x14)
#define SYSTEM_TIMER_C3        (SYSTEM_TIMER_BASE+0x18)

#endif /* SYSTEM_TIMER_H */
