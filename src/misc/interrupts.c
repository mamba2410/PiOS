#include <stdint.h>
#include <sysregs.h>
#include <addresses/irq.h>
#include <misc/interrupts.h>
#include <addresses/local_timer.h>
#include <misc/printf.h>
#include <peripherals/mmio.h>
#include <peripherals/mini_uart.h>
#include <peripherals/uart0.h>
#include <peripherals/timer.h>

char* const IRQ_NAMES[] = {
	"Synchronous Exception EL1t",
	"Interrupt Request EL1t", 
	"Fast Interrupt Request EL1t",
	"System Error EL1t",
	"Synchronous Exception EL1h",
	"Interrupt Request EL1h", 
	"Fast Interrupt Request EL1h",
	"System Error EL1h",
	"Synchronous Exception EL0_32",
	"Interrupt Request EL0_32", 
	"Fast Interrupt Request EL0_32",
	"System Error EL0_32",
	"Synchronous Exception EL0_64",
	"Interrupt Request EL0_64", 
	"Fast Interrupt Request EL0_64",
	"System Error EL0_64",
	"Synchronous Exception EL0_64 ERROR",
	"System Call EL0_64 ERROR",
	"Data Abort EL0_64, invalid memory"
};

/*
 * Handles known interrupts in EL1h
 */
void handle_irq_el1h(){
	uint32_t irq;

	// Peripheral IRQs, register 1
	while( (irq = mmio_get32(IRQ_PENDING_1)) ){		// While there is an IRQ pending
		switch(irq){								// Which IRQ is pending?
			case SYSTEM_TIMER_IRQ_1: handle_system_timer(); break;	
			case AUX_IRQ: handle_aux_irq(); break;
			default: printf("[E] Unknown pending irq (p): %x\n", irq);	// The IRQ is unrecognised and ignored
		}
	}	

	// Peripheral IRQs, register 2
	while( (irq = mmio_get32(IRQ_PENDING_2)) ){
		switch(irq){
			case UART_IRQ: uart0_irq(); break;
			default: printf("[E] Unknown pending irq (p): %x\n", irq+32);	// The IRQ is unrecognised and ignored
		}
	}

	// Core-specific IRQs, core 0
	//while( (irq=mmio_get32(LOCAL_TIMER_CORE0_IRQ_REG)) ) {
	//	switch(irq) {
	//		case LOCAL_TIMER_IRQ: handle_local_timer(); break;
	//		default: printf("[E] Unknown pending irq (c): %x\n", irq);	// The IRQ is unrecognised and ignored
	//	}
	//}

	// Baisc peripheral IRQs
	//while( (irq=mmio_get32(IRQ_BASIC_PENDING)) ) {
	//	switch(irq) {
	//		case LOCAL_TIMER_IRQ: handle_arm_timer(); break;
	//		case PENDING_IRQ1:
	//		case PENDING_IRQ2: break;
	//		default: printf("[E] Unknown pending irq (b): %x\n", irq);
	//	}
	//}
}

/*
 *	Handle interrupts from the AUX.
 *	I think it's just mini uart but I could be wrong.
 *	Note: ALL interrupts from the aux will be handled here so make sure
 *	to properly distinguish between them.
 *	This is lazy and should be changed if any other interrupts are enabled.
 *	See page 10 of 2835 peripherals manual. Proper way to do it is to check 
 *	which interrupt was generated
 */
void handle_aux_irq(){
	mini_uart_irq();
}


/*
 * Prints information about the unhandled interrupt
 */
void show_invalid_entry_message(uint8_t exception_type, uint64_t esr, uint64_t elr){
	printf("\
[E] Exception type: %s (0x%02x);\n\
--> esr: 0x%08x (ec: 0x%02x); elr: 0x%0x\n",
			IRQ_NAMES[exception_type],
			exception_type,
			esr,
			(esr>>ESR_ELx_EC_SHIFT)&0x3f,
			elr
		);
}

void handle_el0_64_unknown(uint64_t esr, uint64_t elr){
	printf("\
[E] An unknown exception occurred at EL0_64_SNC\n\
--> esr: 0x%08x (ec: 0x%02x); elr: 0x%0x\n\
--> likely due to insufficient permissions.\n",
			esr,
			(esr>>ESR_ELx_EC_SHIFT)&0x3f,
			elr
		);
}


/*
 * Enables the interrupt controller
 * move to proc/irq_ctl.c?
 */
void enable_interrupt_controller(){
	mmio_put32(ENABLE_IRQS_1, IER_1_VALUE);
	mmio_put32(ENABLE_IRQS_2, IER_2_VALUE);
}
