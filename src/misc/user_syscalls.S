#include <misc/syscalls.h>

//.section ".text.user"

/*
 * Wrapper function for the write syscall	
 */
.global call_sys_write
call_sys_write:
	mov		x8, #SYSCALL_WRITE	// Load x8 with the ID for write syscall
	svc		#0					// Generate a synchronous exception to go to the interrupt handler
	ret							// Once we are done, return to sender


/*
 * Wrapper function for the clone syscall
 */	
.global call_sys_clone
call_sys_clone:
	mov		x10, x0				// Save function pointer in x10	
	mov		x11, x1				// Save function argument in x11
	mov		x12, x2				// Save stack pointer in x12

	mov		x0, x2				// Put stack in x0
	mov		x8, #SYSCALL_CLONE	// Put clone syscall ID in x8
	svc		0					// Generate synchronous exception
	
	cmp		x0, #0				// Is the return value zero
	beq		thread_start		// If yes, we are child and we start our thread
	ret							// If not, we are parent and return the PID of child

thread_start:
	mov		x29, #0				//
	mov		x0, x11				// Put function argument in x0
	blr		x10					// Branch to function

	mov		x8, #SYSCALL_EXIT	// Load x8 with exit ID
	svc		0					// Generate synchronous exception


/*
 * Wrapper function for the fork syscall
 */
.global call_sys_fork
call_sys_fork:
	mov		x8, #SYSCALL_FORK
	svc		#0
	ret

/*
 * Wrapper function fot the malloc syscall
 */
.global call_sys_malloc
call_sys_malloc:
	mov		w8,	#SYSCALL_MALLOC	// Load register with malloc syscall ID
	svc		#0					// Generate synchronous exception
	ret							// Return to sender


/*
 * Wrapper function for the exit syscall
 */
.global call_sys_exit
call_sys_exit:
 	mov		w8,	#SYSCALL_EXIT	// Load register with exit syscall ID
	svc		#0					// Generate synchronous exception
	ret							// Return to sender

/*
 * Function for user code to delay
 */
.global user_delay
user_delay:
	subs	x0, x0, #1
	bne		user_delay
	ret
