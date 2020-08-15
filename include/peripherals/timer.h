#ifndef TIMER_H
#define TIMER_H

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


void system_timer_init();
void handle_system_timer();

void arm_timer_init();
void handle_arm_timer();
void arm_timer_irq_clear();
uint8_t arm_timer_irq_status();

#endif /* TIMER_H */
