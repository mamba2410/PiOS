#include <addresses/gpio.h>
#include <addresses/mini_uart.h>
#include <peripherals/mmio.h>
#include <peripherals/baud_rate.h>
#include <peripherals/mini_uart.h>

/*
 * Initialise mini uart for io
 */
void mini_uart_init(){
	uint32_t selector;

	selector = mmio_get32(GPFSEL1);		// Grab GPIO selector
	selector &= ~((7<<12) | (7<<15));	// Clean GPIO 14 and 15
	selector |=  ((2<<12) | (2<<15));	// Set them to alt5
	mmio_put32(GPFSEL1, selector);		// Put selector back

	mmio_put32(GPPUD, 0);				// Set pins to be floating, not up or down
	mmio_delay(150);					// Delay 150 clock cycles
	mmio_put32(GPPUDCLK0, (1<<14)|(1<<15));	// Pulse for GPIO 14 and 15
	mmio_delay(150);					// Delay 150 clock cycles
	mmio_put32(GPPUDCLK0, 0);			// Clear pulse

	mmio_put32(AUX_ENABLES, 1);			// Enable mini uart
	mmio_put32(AUX_MU_CNTL_REG, 0);		// Disable auto flow control and disable rx/tx for now

	mmio_put32(AUX_MU_IER_REG, AUX_MU_IER_REG_VAL);		// Set interrupts
	mmio_put32(AUX_MU_LCR_REG, 3);		// Enable 8-bit mode
	mmio_put32(AUX_MU_MCR_REG, 0);		// Set RTS line always high
	mmio_put32(AUX_MU_BAUD_REG, MINI_UART_REG_VAL);	// Set baud rate to 115200

	mmio_put32(AUX_MU_CNTL_REG, 3);		// Enable rx/tx
}

/*
 * Put a single character on the mini uart
 */
void mini_uart_putc(char c){
	while(1){									// Wait...
		if( mmio_get32(AUX_MU_LSR_REG) & 0x20 )	// If register is ready to be written to
			break;								// Break out of loop
	}
	mmio_put32(AUX_MU_IO_REG, c);				// Put character in the io register
}

/*
 * Get single character from mini uart
 */
char mini_uart_getc(){
	char r;
	while(1){									// Wait...
		if( mmio_get32(AUX_MU_LSR_REG) & 0x01 )	// If register has data in it
			break;								// Break out of loop
	}
	r = (mmio_get32(AUX_MU_IO_REG) & 0xff);		// Get character from io register
	return (r=='\r')?'\n':r;					// If character is carriage return, send newline instead
}


/*
 * Put a null-terminated string on the mini uart line
 */
void mini_uart_puts(char* s){
	for(int i = 0; s[i] != '\0'; i++){			// As long as the current character isn't null
		if(s[i] == '\n') mini_uart_putc('\r');	// If the character is a newline, print carriage return as well
		mini_uart_putc(s[i]);					// Put the character on the line
	}
}

void mini_uart_irq(){
	uint8_t i;

	/*
	 * Handle RX interrupts
	 */
	char buf[9];
	for( i=0; mmio_get32(AUX_MU_LSR_REG)&0x01 ; i++ ){
		buf[i] = mini_uart_getc();
		mini_uart_putc(buf[i]);
	}
}

/*
 * Get a string from the mini uart line
 */
//char mini_uart_gets(){}


