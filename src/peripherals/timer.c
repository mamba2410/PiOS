#include <stdint.h>
#include <addresses/arm_timer.h>
#include <addresses/local_timer.h>
#include <addresses/system_timer.h>
#include <peripherals/mmio.h>
#include <proc/tasks.h>
#include <peripherals/timer.h>

#include <misc/printf.h>

static const uint32_t SYSTEM_TIMER_INTERVAL = 200000;	
static const uint32_t ARM_TIMER_INTERVAL = 200000;
static const uint32_t LOCAL_TIMER_INTERVAL = 2e5;		// 28-bit

static uint32_t system_timer_value = 0;

// ========================= SYSTEM TIMER =========================================

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


// =========================== ARM TIMER ==========================================

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


// =========================== LOCAL BCM TIMER ==================================

/*
 *	Initialise the local BCM timer
 *	I am a little confused at this, there are a lot more registers and control options
 *	I think this is the 64-bit timer but the reload value is only 28-bits
 *	There's a difference between the 64-bit timer and the local timer.
 *	Local timer seems to be core-independent but can route the interrupt to a certain
 *	core, whereas the 64-bit timer runs up and is specific to a core?
 */
void local_timer_init() {
	mmio_put32(LOCAL_TIMER_IRQ_ROUTE_REG, LOCAL_TIMER_ROUTE_VAL);	// Route the local timer IRQs to the right core

	uint32_t ctrl_value = LOCAL_TIMER_CTRL_STATUS_VAL | (LOCAL_TIMER_INTERVAL&0x0FFFFFFF);
	mmio_put32(LOCAL_TIMER_STATUS_REG, ctrl_value);					// Set local timer control and interval
	mmio_put32(LOCAL_TIMER_CORE0_TIC_REG, LOCAL_TIMER_TIC_VAL);		// Set the timer interrupt control
}

/*
 *	Called when the local timer interrupts
 */
void handle_local_timer() {
	local_timer_clear_irq();
	printf("[I] Local timer interrupt\n");
	schedule_tick();
}


/*
 *	Clear interrupts for the local timer
 */
void local_timer_clear_irq() {
	mmio_put32(LOCAL_TIMER_CLR_REG, LOCAL_TIMER_INT_PENDING);
}
