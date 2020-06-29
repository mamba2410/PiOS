#include <testing.h>
#include <peripherals/mmio.h>
#include <misc/printf.h>
#include <misc/syscalls.h>
#include <proc/fork.h>
#include <proc/tasks.h>

extern uint64_t get_exception_level();

void testing_main(){
	int32_t result;
	result = create_process(PF_KERNEL_THREAD, (uint64_t)(&kernel_process), 0, 0);
	if( result < 0 ){ printf("Error whilst starting kernel process\n"); return; }
}

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

	//sprintf(buf, "User process started at EL%d\n", get_exception_level());
	//call_sys_write(buf);

	char ep_str1[8] = "12345";
	char ep_str2[8] = "abcde";

	stack = call_sys_malloc();
	if(stack < 0){ printf("Error whilst allocating user process 1 stack\n"); return; }
	error = call_sys_clone((uint64_t)(&example_process), (uint64_t)(ep_str1), stack);
	if(error < 0){ printf("Error whilst cloning user process 1\n"); return;}

	stack = call_sys_malloc();
	if(stack < 0){ printf("Error whilst allocating user process 2 stack\n"); return; }
	error = call_sys_clone((uint64_t)(&example_process), (uint64_t)(ep_str2), stack);
	if(error < 0){ printf("Error whilst cloning user process 2\n"); return;}

	printf("Number of tasks running: %d\n", number_tasks);

	call_sys_exit();
}

void kernel_process(){
	printf("Kernel process started at EL%d\n", get_exception_level());
	int32_t error = move_to_user((uint64_t)(&user_process));
	if(error < 0) printf("Error whilst moving kernel process to user mode.\n");
	printf("Number of tasks running: %d\n", number_tasks);
	printf("Kernel process done\n");
}

