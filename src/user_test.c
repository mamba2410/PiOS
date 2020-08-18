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
	call_sys_write("[U] User process stared\n");

	int32_t pid = call_sys_fork();
	if(pid < 0) {
		call_sys_write("[E] Error when forking user process\n");
		call_sys_exit();
		return;
	}

	call_sys_write("[D] Post-fork, PID: ");
	char buf[3] = "0\n\0";
	buf[0] += pid;
	call_sys_write(buf);

	char bufa[] = "abcde";
	char buf1[] = "12345";

	if(pid == 0)	example_process(bufa);
	else			example_process(buf1);
}
