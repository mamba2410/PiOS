#include <serial/printf.h>
#include <stdint.h>

extern uint8_t get_exception_level();

// Main function passed to by boot.S
void kernel_main(void){

	uart_init();		// Initialise uart

	printf("Initialised uart!\n");

	uint8_t exception_level;
	exception_level = get_exception_level();
	printf("Exception level: %x\n", exception_level);
	
	char c;
	// Forever...
	while(1){
		// Just echo the input from the serial back
		c = uart_getc();
		uart_putc(c);
		
	}

	
}
