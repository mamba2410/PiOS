#include <serial/mini_uart.h>
#include <mmio.h>
#include <stdint.h>

void	mini_uart_init(){

	uint32_t selector;

	selector = mmio_get32(GPFSEL1);		// Grab GPIO selector
	selector &= ~((7<<12) | (7<<15));	// Clean GPIO 14 and 15
	selector |=  ((2<<12) | (2<<15));	// Set them to alt5

	mmio_put32(GPFSEL1, selector);		// Put selector back

	// Set pins 14 and 15 to floating
	// i.e. not pulled up or down
	mmio_put32(GPPUD, 0);
	mmio_delay(150);
	mmio_put32(GPPUDCLK0, (1<<14)|(1<<15));	// Enable GPIO 14 and 15
	mmio_delay(150);
	mmio_put32(GPPUDCLK0, 0);

	// Initialising the mini uart
	mmio_put32(AUX_ENABLES, 1);		// Enable mini uart
	mmio_put32(AUX_MU_CNTL_REG, 0);	// Disable auto flow control and disable rx/tx for now

	mmio_put32(AUX_MU_IER_REG, 0);		// Disable rx/tx interrupts
	mmio_put32(AUX_MU_LCR_REG, 3);	// Enable 8-bit mode
	mmio_put32(AUX_MU_MCR_REG, 0);	// Set RTS line always high
	mmio_put32(AUX_MU_BAUD_REG, 270);	// Set baud rate to 115200

	mmio_put32(AUX_MU_CNTL_REG, 3);	// Enable rx/tx
}

char	mini_uart_getc(){
	char r;
	while(1){
		if( mmio_get32(AUX_MU_LSR_REG) & 0x01 )
			break;
	}
	r = (mmio_get32(AUX_MU_IO_REG) & 0xff);
	return (r=='\r')?'\n':r;
}

// char	mini_uart_gets(){}

void	mini_uart_putc(char c){
	while(1){
		if( mmio_get32(AUX_MU_LSR_REG) & 0x20 )
			break;
	}
	mmio_put32(AUX_MU_IO_REG, c);
}

void	mini_uart_puts(char* s){
	for(int i = 0; s[i] != '\0'; i++){
		if(s[i] == '\n') mini_uart_putc('\r');
		mini_uart_putc(s[i]);
	}
}
