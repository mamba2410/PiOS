#include <uart/mini_uart.h>
#include <uart/mmio.h>

// Main function passed to by boot.S
void kernel_main(void){

	// There is literally nothing here, no heap or anything
	// No stdout either because where would that even go?

	// Can use Pi3 mini uart on pins 14 and 15
	// This is probably the best way to get output from pi
	// Currently

	// Initialise the mini uart
	// Working with the mini uart instead of the PL011 uart because it's apparently simpler
	mini_uart_init();
	// Put a string to the uart bus
	mini_uart_puts("Hello, World!\n");
	mini_uart_puts("This is a new line\n");

	
	char c;
	// Forever...
	while(1){
		// Just echo the input from the serial back
		c = mini_uart_getc();
		mini_uart_putc(c);
		
		// Temporary to find out if it works
		//mini_uart_puts("Hello, World!\r\n");
		//mmio_delay(1000);
	}


	// Once this function ends, I don't know what happens as there's no catch on the boot.S
}
