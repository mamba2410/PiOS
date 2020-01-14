#include <system/system_timer.h>
#include <mmio/mmio.h>

#include <serial/printf.h>

static const uint32_t SYSTEM_TIMER_INTERVAL = 200000;
static uint32_t current_timer_value = 0;

/*
 * Handle system timer interrupt request
 */
void handle_system_timer(){
	current_timer_value += SYSTEM_TIMER_INTERVAL;
	mmio_put32(TIMER_C1, current_timer_value);
	mmio_put32(TIMER_CS, TIMER_CS_M1);
}

/*
 * Initialise the system timer with some nonzero value set by the interval
 */
void system_timer_init(){
	current_timer_value = mmio_get32(TIMER_CLO);
	current_timer_value += SYSTEM_TIMER_INTERVAL;
	mmio_put32(TIMER_C1, current_timer_value);
}
