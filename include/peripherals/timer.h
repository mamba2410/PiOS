#ifndef TIMER_H
#define TIMER_H

/*
 *	Values for the system timer, 
 */

#define SYSTEM_TIMER_CS_M0	(1 << 0)
#define SYSTEM_TIMER_CS_M1	(1 << 1)
#define SYSTEM_TIMER_CS_M2	(1 << 2)
#define SYSTEM_TIMER_CS_M3	(1 << 3) 


/*
 *	Values for ARM timer, page 196 of BCM2837 ARM peripherals manual
 */

#define ARM_TIMER_FRC_PRESCALER_SHIFT	16		// Prescaler is bits 23:16 in CTRL register
#define ARM_TIMER_FRC_PRESCALER			0x3E	// Default is 0x3E, freq=sys_clk/(prescale+1)

#define ARM_TIMER_FRC_EN		(1<<9)		// Enable free-running counter
#define ARM_TIMER_DBG_HLT		(1<<8)		// 1 - Halt timer if ARM is in debug halted mode
#define ARM_TIMER_EN			(1<<7)		// Enable ARM timer
#define ARM_TIMER_IRQ_EN		(1<<5)		// 1 - Interrupts enabled
#define ARM_TIMER_PRE_NONE		(0b00<<2)	// 0b00 - pre-scale = clk/1
#define ARM_TIMER_PRE_16		(0b01<<2)	// 0b01 - pre-scale = clk/16
#define ARM_TIMER_PRE_256		(0b10<<2)	// 0b10 - pre-scale = clk/256
#define ARM_TIMER_32BIT			(1<<1)		// 0-16-bit; 1-32-bit
#define ARM_TIMER_CTRL_VAL		(ARM_TIMER_32BIT|ARM_TIMER_PRE_NONE|ARM_TIMER_IRQ_EN|ARM_TIMER_EN)


/*
 *	Values for the local timer, https://github.com/s-matyukevich/raspberry-pi-os/issues/70
 */

#define LOCAL_TIMER_EN			(1<<28)		// Enable local timer
#define LOCAL_TIMER_IE			(1<<29)		// Enable interrupts for the local timer
#define LOCAL_TIMER_INT_PENDING	(1<<31)		// Set to 1 if the local timer has an interrupt pending
#define LOCAL_TIMER_CTRL_STATUS_VAL	(LOCAL_TIMER_EN|LOCAL_TIMER_IE)

#define LOCAL_TIMER_INC2		(1<<9)		// Increment the local timer by 2 if set
#define LOCAL_TIMER_APBCLK		(1<<8)		// Use the APB clock instead of a crystal one
#define LOCAL_TIMER_CTRL_VAL	(0)

#define LOCAL_TIMER_nCNTPSIRQ	(1<<0)		// ??? Set to 1 to enable the IRQ
#define LOCAL_TIMER_nCNTPNSIRQ	(1<<1)		//
#define LOCAL_TIMER_nCNTHPIRQ	(1<<2)
#define LOCAL_TIMER_nCNTVIRQ	(1<<3)
#define LOCAL_TIMER_nCNTALL		(0xF)
#define LOCAL_TIMER_TIC_VAL		LOCAL_TIMER_nCNTALL

#define LOCAL_TIMER_ROUTE_CORE0	(0b000)
#define LOCAL_TIMER_ROUTE_CORE1	(0b001)
#define LOCAL_TIMER_ROUTE_CORE2	(0b010)
#define LOCAL_TIMER_ROUTE_CORE3	(0b011)
#define LOCAL_TIMER_ROUTE_VAL	(LOCAL_TIMER_ROUTE_CORE0)


#include <stdint.h>

void system_timer_init();
void handle_system_timer();

void arm_timer_init();
void handle_arm_timer();
void arm_timer_irq_clear();
uint8_t arm_timer_irq_status();

void local_timer_init();
void local_timer_clear_irq();
void handle_local_timer();

uint64_t get_local_timer_value();
void set_local_timer_value(uint64_t);

#endif /* TIMER_H */
