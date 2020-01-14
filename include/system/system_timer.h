#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

#include <mmio/mmio.h>

#define TIMER_CS        ((uint64_t*)(MMIO_BASE+0x00003000))
#define TIMER_CLO       ((uint64_t*)(MMIO_BASE+0x00003004))
#define TIMER_CHI       ((uint64_t*)(MMIO_BASE+0x00003008))
#define TIMER_C0        ((uint64_t*)(MMIO_BASE+0x0000300C))
#define TIMER_C1        ((uint64_t*)(MMIO_BASE+0x00003010))
#define TIMER_C2        ((uint64_t*)(MMIO_BASE+0x00003014))
#define TIMER_C3        ((uint64_t*)(MMIO_BASE+0x00003018))

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3) 


void system_timer_init();
void handle_timer_irq();

#endif /* SYSTEM_TIMER_H */
