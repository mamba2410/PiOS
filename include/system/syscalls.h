#ifndef SYSCALLS_H
#define SYSCALLS_H

#define SYSCALL_WRITE	0x0
#define	SYSCALL_CLONE	0x1
#define	SYSCALL_MALLOC	0x2
#define	SYSCALL_EXIT	0x3
#define SYSCALL_TOTAL	0x4

#ifndef __ASSEMBLER__
#include <stdint.h>

void	 sys_write(char*);
uint8_t	 sys_clone(uint64_t);
uint64_t sys_malloc();
void	 sys_exit();

extern void	 	call_sys_write(char*);
extern uint8_t	call_sys_clone(uint64_t func, uint64_t arg, uint64_t sp);
extern uint64_t call_sys_malloc();
extern void	 	call_sys_exit();


#endif /* __ASSEMBLER__ */

#endif /* SYSCALLS_H */
