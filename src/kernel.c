#include <stdint.h>
#include <mmio/interrupts.h>
#include <mmio/mailbox.h>
#include <mmio/mmio.h>
#include <serial/baud_rate.h>
#include <serial/printf.h>
#include <system/fork.h>
#include <system/syscalls.h>
#include <system/timer.h>
#include <system/tasks.h>
#include <testing.h>

extern uint64_t get_exception_level();

// Main function passed to by boot.S
void kernel_main(void){
#ifdef PRINTF_UART0
	uart0_init();					// Initialise uart device
#else
	mini_uart_init();
#endif /* PRINTF_UART0 */
	printf(" Kernel started at EL%d\n", get_exception_level());
	interrupt_vector_table_init();	// Initialise interrupt vector table
	system_timer_init();			// Initialise system timer
	enable_interrupt_controller();	// Enable interrupt controller
	unmask_irq();					// Allow IRQs
	printf(" Setup done\n");

	testing_main();					// Begin testing code

	printf(" kernel_main done, scheduling\n");
	while(1) schedule();	// Schedule infinitely
}	// Should not exit

