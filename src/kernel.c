#include <stdint.h>
#include <mmio/interrupts.h>
#include <mmio/mailbox.h>
#include <mmio/mmio.h>
#include <serial/baud_rate.h>
#include <serial/printf.h>
#include <system/timer.h>
#include <system/tasks.h>
#include <system/fork.h>

// Just repeatedly print the first 5 characters of a given string
void example_process(char *str){
	while(1){
		for(uint8_t i = 0; i < 5; i++){
			uart_putc(str[i]);
			mmio_delay(1e6);
		}
	}
}

void kernel_process(){
	printf("Kernel process started. EL%d\n", get_exception_level());
	int32_t error = move_to_user((uint64_t)(&user_process));
	if(error < 0) printf("Error whilst moving kernel process to user mode.\n");
}

void user_process(){
	char buf[32] = {0};
	sprintf(buf, "User process started at EL%d\n", get_exception_level());
	call_sys_write(buf);
}

// Main function passed to by boot.S
void kernel_main(void){
	int8_t result;

	uart_init();		// Initialise uart
	printf("Initialised uart!\n");
	printf("IBRD:%u\tFBRD:%u\n", IBRD_VALUE, FBRD_VALUE);
	printf("Exceptino level EL%d\n", get_exception_level());

	// Get the serial number of the board with mailboxes
	mailbox[0] = 8 *sizeof(mailbox[0]);			// Size of mailbox message in bytes ( 8 times uint32_t)
	mailbox[1] = MBOX_REQUEST;					// Request magic value, indicates we want a request
	mailbox[2] = MBOX_TAG_GETSERIAL;			// Tag identifier to get serial number
	mailbox[3] = 8;
	mailbox[4] = 8;
	mailbox[5] = 0;
	mailbox[6] = 0;
	mailbox[7] = MBOX_TAG_LAST;					// Last tag magic value

	if( !mailbox_call(MBOX_CH_PROP) ) printf("Serial number is %08x %08x\n", mailbox[6], mailbox[5]);
	else printf("Unable to query serial\n");

	interrupt_vector_table_init();
	system_timer_init();
	enable_interrupt_controller();
	unmask_irq();

	printf("Interrupts initialised, forking processes\n");

	result = create_process( (uint64_t)(&example_process), (uint64_t)"abcde" );
	if(result){ printf("Error whilst starting process 1\n"); return; }
	result = create_process( (uint64_t)(&example_process), (uint64_t)"12345" );
	if(result){ printf("Error whilst starting process 2\n"); return; }
	

	printf("Processes forked, starting schedule loop\n");
	
	// Nothing left for the kernel to do, so just schedule other tasks
	while(1){
		schedule();
	}

	// Should not exit
}

