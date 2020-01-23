#ifndef TIMER_H
#define TIMER_H

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3) 

void system_timer_init();
void handle_system_timer();

#endif /* TIMER_H */
