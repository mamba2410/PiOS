#include <stdint.h>
#include <addresses/timer.h>
#include <addresses/local_timer.h>
#include <peripherals/mmio.h>
#include <proc/tasks.h>
#include <peripherals/timer.h>

static const uint32_t SYSTEM_TIMER_INTERVAL = 200000;
static uint32_t current_timer_value = 0;

static const uint32_t LOCAL_TIMER_INTERVAL = 200000;

/*
 * Handle system timer interrupt request
 */
void handle_system_timer(){
	current_timer_value += SYSTEM_TIMER_INTERVAL;
	mmio_put32(TIMER_C1, current_timer_value);
	mmio_put32(TIMER_CS, TIMER_CS_M1);

	schedule_tick();
}

/*
 * Initialise the system timer with some nonzero value set by the interval
 */
void system_timer_init(){
	current_timer_value = mmio_get32(TIMER_CLO);
	current_timer_value += SYSTEM_TIMER_INTERVAL;
	mmio_put32(TIMER_C1, current_timer_value);
}


/*
 *	Handle local timer interrupt
 *	Just call the schedule function
 */
void handle_local_timer() {
	local_timer_irq_clear();
	schedule_tick();
}

/*
 *	Initialise the local timer
 */
void local_timer_init() {
	mmio_put32(LOCAL_TIMER_CTRL_REG, LOCAL_TIMER_CTRL_VAL);
	mmio_put32(LOCAL_TIMER_LOAD_REG, LOCAL_TIMER_INTERVAL);
}


/*
 *	Clear pending interrupt for the local timer
 */
void local_timer_irq_clear() {
	mmio_put32(LOCAL_TIMER_IRQCA_REG, 1);
}

/*
 *	Get the interrupt status
 *	0 - Interrupt line not asserted
 *	1 - Interrupt line asserted
 */
uint8_t local_timer_irq_status() {
	return mmio_get32(LOCAL_TIMER_MASKIRQ_REG);
}
