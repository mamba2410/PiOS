#include <serial/printf.h>
#include <stdint.h>
#include <mmio/mailbox.h>

extern uint8_t get_exception_level();

// Main function passed to by boot.S
void kernel_main(void){

	uart_init();		// Initialise uart
	printf("Initialised uart!\n");

	// Get and print exception level
	uint8_t exception_level;
	exception_level = get_exception_level();
	printf("Exception level: %x\n", exception_level);

	// Get the serial number of the board with mailboxes
	mailbox[0] = 8 *sizeof(mailbox[0]);			// Size of mailbox message in bytes ( 8 times uint32_t)
	mailbox[1] = MBOX_REQUEST;					// Request magic value, indicates we want a request
	mailbox[2] = MBOX_TAG_GETSERIAL;			// Tag identifier to get serial number
	mailbox[3] = 8;
	mailbox[4] = 8;
	mailbox[5] = 0;
	mailbox[6] = 0;
	mailbox[7] = MBOX_TAG_LAST;					// Last tag magic value

	//printf("Initialised mailbox!\n");

	
	if( !mailbox_call(MBOX_CH_PROP) )
		printf("Serial number is %08x%08x\n", mailbox[6], mailbox[5]);
	else
		printf("Unable to query serial\n");
	
	
	// Go into an echo loop
	printf("Echoing\n");
	while(1){
		uart_putc( uart_getc() );
		
	}

	
}
