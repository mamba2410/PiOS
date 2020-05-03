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

extern uint64_t get_exception_level();

// Just repeatedly print the first 5 characters of a given string
void example_process(char *str){
	char buf[] = {0, 0};
	while(1){
		for(uint8_t i = 0; i < 5; i++){
			buf[0] = str[i];
			call_sys_write(buf);
			mmio_delay(1e6);
		}
	}
}

void user_process(){
	char buf[64] = "\0";
	uint64_t stack;
	int32_t error;
	uint64_t el = 0;

	//el = get_exception_level();
	sprintf(buf, "User process started at EL%d\n", el);
	call_sys_write(buf);


	char ep_str1[8] = "12345";
	char ep_str2[8] = "abcde";


	//sprintf(ep_str1, "EL%d", get_exception_level());
	//sprintf(ep_str2, "el%d", get_exception_level());

	stack = call_sys_malloc();
	if(stack < 0){ printf("Error whilst allocating user process 1 stack\n"); return; }
	error = call_sys_clone((uint64_t)(&example_process), (uint64_t)(ep_str1), stack);
	if(error < 0){ printf("Error whilst cloning user process 1\n"); return;}

	stack = call_sys_malloc();
	if(stack < 0){ printf("Error whilst allocating user process 2 stack\n"); return; }
	error = call_sys_clone((uint64_t)(&example_process), (uint64_t)(ep_str2), stack);
	if(error < 0){ printf("Error whilst cloning user process 2\n"); return;}

	call_sys_exit();
}

void kernel_process(){
	printf("Kernel process started. EL%d\n", get_exception_level());
	int32_t error = move_to_user((uint64_t)(&user_process));
	if(error < 0) printf("Error whilst moving kernel process to user mode.\n");
	printf("Kernel process done\n");
}

// Main function passed to by boot.S
void kernel_main(void){
	int32_t result;

	uart_init();		// Initialise uart
	printf("\n Exception level EL%d\n", get_exception_level());

	interrupt_vector_table_init();
	system_timer_init();
	enable_interrupt_controller();
	unmask_irq();

	printf(" Setup done\n");

	char buf[32];
	sprintf(buf, "sprintf EL %d\n", get_exception_level());
	printf(buf);
	

	result = create_process(PF_KERNEL_THREAD, (uint64_t)(&kernel_process), 0, 0);
	if( result < 0 ){ printf("Error whilst starting kernel process\n"); return; }
	

	
	printf(" kernel_main done, scheduling\n");
	while(1) schedule();	// Schedule infinitely
}	// Should not exit

