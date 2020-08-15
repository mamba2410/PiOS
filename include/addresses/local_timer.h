#ifndef ADDR_LOCAL_TIMER_H
#define ADDR_LOCAL_TIMER_H

#include <addresses/addr_base.h>

#define LOCAL_TIMER_BASE			LOCAL_BASE
#define LOCAL_TIMER_CTRL_REG		(LOCAL_TIMER_BASE)
#define LOCAL_TIMER_LS_REG			(LOCAL_TIMER_BASE+0x1C)
#define LOCAL_TIMER_MS_REG			(LOCAL_TIMER_BASE+0x20)
#define LOCAL_TIMER_IRQ_ROUTE_REG	(LOCAL_TIMER_BASE+0x24)
#define LOCAL_TIMER_STATUS_REG		(LOCAL_TIMER_BASE+0x34)		// Local timer status and control
#define LOCAL_TIMER_CLR_REG			(LOCAL_TIMER_BASE+0x38)		// Local timer clear and reload
#define LOCAL_TIMER_CORE0_TIC_REG	(LOCAL_TIMER_BASE+0x40)		// Core 0 timer interrupt control
#define LOCAL_TIMER_CORE1_TIC_REG	(LOCAL_TIMER_BASE+0x44)		// Core 1 timer interrupt control
#define LOCAL_TIMER_CORE2_TIC_REG	(LOCAL_TIMER_BASE+0x48)		// Core 2 timer interrupt control
#define LOCAL_TIMER_CORE3_TIC_REG	(LOCAL_TIMER_BASE+0x4C)		// Core 3 timer interrupt control
#define LOCAL_TIMER_CORE0_IRQ_REG	(LOCAL_TIMER_BASE+0x60)		// Core 0 IRQ source
#define LOCAL_TIMER_CORE1_IRQ_REG	(LOCAL_TIMER_BASE+0x64)		// Core 1 IRQ source
#define LOCAL_TIMER_CORE2_IRQ_REG	(LOCAL_TIMER_BASE+0x68)		// Core 2 IRQ source
#define LOCAL_TIMER_CORE3_IRQ_REG	(LOCAL_TIMER_BASE+0x6C)		// Core 3 IRQ source

#endif /* ADDR_LOCAL_TIMER_H */
