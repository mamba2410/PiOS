#ifndef SYSCALLS_H
#define SYSCALLS_H

#define SYSCALL_WRITE	0x1
#define	SYSCALL_CLONE	0x2
#define	SYSCALL_MALLOC	0x3
#define	SYSCALL_EXIT	0x4
#define SYSCALL_TOTAL	4

#ifndef __ASSEMBER__

void	 sys_write(char*);
uint8_t	 sys_clone(uint64_t);
uint64_t sys_malloc();
void	 sys_exit();


#endif /* __ASSEMBLER__ */

#endif /* SYSCALLS_H */
