#include <serial/printf.h>
#include <stdint.h>
#include <mmio/mailbox.h>
#include <mmio/interrupts.h>
#include <system/system_timer.h>
#include <system/tasks.h>
#include <system/fork.h>

extern uint8_t get_exception_level();


// Just repeatedly print the first 5 characters of a given string
void example_process(char *str){
	while(1){
		for(uint8_t i = 0; i < 5; i++){
			uart_putc(str[i]);
			mmio_delay(1e5);
		}
	}
}

// Main function passed to by boot.S
void kernel_main(void){
	uart_init();		// Initialise uart
	printf("Initialised uart!\n");

	//current_task = &init_task;
	//tasks[0] = &init_task;

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
		printf("Serial number is %08x %08x\n", mailbox[6], mailbox[5]);
	else
		printf("Unable to query serial\n");

	printf("Initialising interrupts and the system timer\n");
	// Initialise interrupts and system timer
	interrupt_vector_table_init();
	system_timer_init();
	enable_interrupt_controller();
	unmask_irq();

	printf("Interrupts initialised, forking processes\n");

	printf("IBRD:%08x\tFBRD:%08x\n", IBRD_VALUE, FBRD_VALUE);

	int8_t result;

	result = create_process( (uint64_t)(&example_process), "abcde" );
	if(result){ printf("Error whilst starting process 1\n"); return; }
	result = create_process( (uint64_t)(&example_process), "12345" );
	if(result){ printf("Error whilst starting process 2\n"); return; }
	

	printf("Processes forked, starting schedule loop\n");
	
	// Nothing left for the kernel to do, so just schedule other tasks
	while(1){
		schedule();
	}

	
}
