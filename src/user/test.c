#include <user/test.h>
#include <stdint.h>
#include <misc/syscalls.h>

// Just repeatedly print the first 5 characters of a given string
void example_process(char *str){
	char buf[2] = "";
	while(1) {
		for(uint8_t i = 0; str[i] != 0; i++){
			buf[0] = str[i];
			sys_write(buf);
			user_delay(1e6);
		}
	}
}

void user_process(){
	sys_write("[U] User process started\n");

	int32_t pid = sys_fork();
	if(pid < 0) {
		sys_write("[E] Error when forking user process\n");
		sys_exit();
		return;
	}

	sys_write("\n[U] Returned from fork with pid ");
	char buf[] = "0\n";
	buf[0] += pid;
	sys_write(buf);

	if(!pid)	example_process("12345");
	else		example_process("abcde");
}
