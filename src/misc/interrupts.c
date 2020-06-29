#include <stdint.h>
#include <sysregs.h>
#include <addresses/irq.h>
#include <misc/interrupts.h>
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
	"System Call EL0_64 ERROR"
};

/*
 * Handles known interrupts in EL1h
 */
void handle_irq_el1h(){
	uint32_t irq;
	
	while( (irq = mmio_get32(IRQ_PENDING_1)) ){		// While there is an IRQ pending
		switch(irq){								// Which IRQ is pending?
			case SYSTEM_TIMER_IRQ_1:				// If its system timer 1...
				handle_system_timer();				// ...call a separate function
				break;	
			case AUX_IRQ:							// Handle auxiliary iRQ (mini uart?)
				handle_aux_irq();
				break;
			default:								// Else
				printf("Unknown pending irq: %x\n", irq);	// The IRQ is unrecognised and ignored
		}
	}	

	while( (irq = mmio_get32(IRQ_PENDING_2)) ){
		switch(irq){
			case UART_IRQ:
				handle_uart_irq();					// Handle uart0 irq
				break;
			default:								// Else
				printf("Unknown pending irq: %x\n", irq);	// The IRQ is unrecognised and ignored
		}
	}
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
	// TODO: Code does not link if I uncomment this and am not using mini uart as printf
	//mini_uart_putc(mini_uart_getc());
}

/*
 *	Handle all interrupts from the PL011 UART
 *	Again, this handles all interrupts form the PL011 UART so should really
 *	poll to see which interrupt was actually generated before responding.
 *	This is only designed for UART_RX
 */
void handle_uart_irq(){
	uart0_putc( uart0_getc() );
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
