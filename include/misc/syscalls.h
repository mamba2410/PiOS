#ifndef SYSCALLS_H
#define SYSCALLS_H

#define SYSCALL_WRITE	0x0
#define	SYSCALL_CLONE	0x1
#define	SYSCALL_MALLOC	0x2
#define	SYSCALL_EXIT	0x3
#define SYSCALL_FORK	0x4
#define SYSCALL_TOTAL	0x5

#ifndef __ASSEMBLER__
#include <stdint.h>

void	 _sys_write(char*);
uint8_t	 _sys_clone(uint64_t);
int32_t	 _sys_fork();
uint64_t _sys_malloc();
void	 _sys_exit();

extern void	 	sys_write(char*);
extern uint8_t	sys_clone(uint64_t func, uint64_t arg, uint64_t sp);
extern int32_t	sys_fork();
extern uint64_t sys_malloc();
extern void	 	sys_exit();
extern void		user_delay(uint64_t);


#endif /* __ASSEMBLER__ */

#endif /* SYSCALLS_H */
