#include <serial/mini_uart.h>
#include <serial/printf.h>
#include <stdint.h>

extern uint8_t get_exception_level();

// Main function passed to by boot.S
void kernel_main(void){

	// Working with the mini uart instead of the PL011 uart because it's apparently simpler
	mini_uart_init();	// Initialise mini uart

	printf("Initialised uart\n");

	uint8_t exception_level;

	exception_level = get_exception_level();

	// Put a string to the uart bus
	printf("Exception level: %x\n", exception_level);
	
	char c;
	// Forever...
	while(1){
		// Just echo the input from the serial back
		c = mini_uart_getc();
		mini_uart_putc(c);
		
	}

	
}
