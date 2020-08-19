#include <testing.h>
#include <peripherals/mmio.h>
#include <misc/printf.h>
#include <misc/syscalls.h>
#include <proc/fork.h>
#include <proc/tasks.h>
#include <user_test.h>

void testing_main(){
	int32_t result;
	result = create_process(PF_KERNEL_THREAD, (uint64_t)(&kernel_process), 0);
	if( result < 0 ){ printf("[E] Error whilst starting kernel process\n"); return; }
}

void kernel_process(){
	uint64_t start	= (uint64_t)&__user_start;
	uint64_t end	= (uint64_t)&__user_end;
	uint64_t proc	= (uint64_t)&user_process;

	printf("[T] Kernel process started at EL%d\n", get_exception_level());
	int8_t error = move_to_user(start, end-start, proc-start);
	if(error < 0) printf("[E] Error whilst moving kernel process to user mode.\n");

	printf("[T] Kernel process done\n");
	return;
}

