#include <stdint.h>
#include <addresses/irq.h>
#include <mmio/interrupts.h>
#include <mmio/mmio.h>
#include <serial/printf.h>
#include <system/timer.h>

/*
 * Handles known interrupts in EL1h
 */
void handle_irq_el1h(){
	uint32_t irq = mmio_get32(IRQ_PENDING_1);	// Get the IRQ

	switch(irq){								// Which IRQ is pending?
		case SYSTEM_TIMER_IRQ_1:				// If its system timer 1...
			handle_system_timer();				// ...call a separate function
			break;	
		default:								// Else
			printf("Unknown pending irq: %x\n", irq);	// The IRQ is unrecognised and ignored
	}
}

/*
 * Prints information about the unhandled interrupt
 */
void show_invalid_entry_message(uint8_t exception_type, uint64_t esr, uint64_t *elr){
	printf("Exception type: %X; esr: %x; elr: %x\n", exception_type, esr, elr);
}


/*
 * Enables the interrupt controller
 */
void enable_interrupt_controller(){
	mmio_put32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
}
