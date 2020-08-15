#include <stdint.h>
#include <addresses/arm_timer.h>
#include <addresses/local_timer.h>
#include <addresses/system_timer.h>
#include <peripherals/mmio.h>
#include <proc/tasks.h>
#include <peripherals/timer.h>

static const uint32_t SYSTEM_TIMER_INTERVAL = 200000;
static uint32_t system_timer_value = 0;

static const uint32_t ARM_TIMER_INTERVAL = 200000;

/*
 * Handle system timer interrupt request
 */
void handle_system_timer(){
	system_timer_value += SYSTEM_TIMER_INTERVAL;
	mmio_put32(SYSTEM_TIMER_C1, system_timer_value);
	mmio_put32(SYSTEM_TIMER_CS, SYSTEM_TIMER_CS_M1);

	schedule_tick();
}

/*
 * Initialise the system timer with some nonzero value set by the interval
 */
void system_timer_init(){
	system_timer_value = mmio_get32(SYSTEM_TIMER_CLO);
	system_timer_value += SYSTEM_TIMER_INTERVAL;
	mmio_put32(SYSTEM_TIMER_C1, system_timer_value);
}


/*
 *	Handle arm timer interrupt
 *	Just call the schedule function
 */
void handle_arm_timer() {
	arm_timer_irq_clear();
	schedule_tick();
}

/*
 *	Initialise the ARM timer
 */
void arm_timer_init() {
	mmio_put32(ARM_TIMER_CTRL_REG, ARM_TIMER_CTRL_VAL);
	mmio_put32(ARM_TIMER_LOAD_REG, ARM_TIMER_INTERVAL);
}


/*
 *	Clear pending interrupt for the local timer
 */
void arm_timer_irq_clear() {
	mmio_put32(ARM_TIMER_IRQCA_REG, 1);
}

/*
 *	Get the interrupt status
 *	0 - Interrupt line not asserted
 *	1 - Interrupt line asserted
 */
uint8_t arm_timer_irq_status() {
	return mmio_get32(ARM_TIMER_MASKIRQ_REG);
}
