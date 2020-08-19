#include <user_test.h>
#include <stdint.h>
#include <misc/syscalls.h>

// Just repeatedly print the first 5 characters of a given string
void example_process(char *str){
	char buf[2] = {""};
	while(1) {
		for(uint8_t i = 0; str[i] != 0; i++){
			buf[0] = str[i];
			call_sys_write(buf);
			user_delay(1e6);
		}
	}
}

void user_process(){
	call_sys_write("[U] User process started\n");

	int32_t pid = call_sys_fork();
	if(pid < 0) {
		call_sys_write("[E] Error when forking user process\n");
		call_sys_exit();
		return;
	}

	call_sys_write("\n[U] Returned from fork with pid ");
	char buf[] = "0\n";
	buf[0] += pid;
	call_sys_write(buf);

	if(!pid)	example_process("12345");
	else		example_process("abcde");
}
