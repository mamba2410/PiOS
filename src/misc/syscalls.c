#include <stdint.h>
#include <memory/mem.h>
#include <misc/printf.h>
#include <misc/syscalls.h>
#include <proc/fork.h>


/*
 * Syscall to write to the console
 * Currently printf serial, also does not do any formatting, just writes
 */
void sys_write(char* buf){
	printf(buf);
}


/*
 * Clones a process given a stack pointer for the new process
 * Will be in user mode
 * NOTE: Does not work for now in virtual memory, function pointers will be off
 */
uint8_t sys_clone(uint64_t stack){
	//return create_process(0, 0, 0, stack);
	return 0xFF;
}

/*
 * Forks a process, both tasks will be exactly the same, with
 * separate virtual memory and PIDs
 */
int32_t sys_fork() {
	//printf("[D] Forking at EL %d\n", get_exception_level());
	return create_process(0, 0, 0);
}


/*
 * Allocates a new memory page 
 */
uint64_t sys_malloc(){
	uint64_t page = get_page();
	if(!page) return -1;
	return page;
}


/*
 * Exits a process and cleans it up properly
 */
void sys_exit(){
	exit_process();
}

void* const syscall_table[] = {sys_write, sys_clone, sys_malloc, sys_exit, sys_fork};
