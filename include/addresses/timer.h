#ifndef ADDR_TIMER_H
#define ADDR_TIMER_H

#include <addresses/addr_base.h>

#define TIMER_BASE		(MMIO_BASE+0x00003000)

#define TIMER_CS        (TIMER_BASE+0x00)
#define TIMER_CLO       (TIMER_BASE+0x04)
#define TIMER_CHI       (TIMER_BASE+0x08)
#define TIMER_C0        (TIMER_BASE+0x0C)
#define TIMER_C1        (TIMER_BASE+0x10)
#define TIMER_C2        (TIMER_BASE+0x14)
#define TIMER_C3        (TIMER_BASE+0x18)

#endif /* TIMER_H */
