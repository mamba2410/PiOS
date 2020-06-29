#ifndef FORK_H
#define FORK_H

#include <stdint.h>
#include <proc/tasks.h>


/*
 * Program status register bits to change to different modes
 */
#define PSR_MODE_EL0t	0x00000000
#define PSR_MODE_EL1t	0x00000004
#define PSR_MODE_EL1h	0x00000005
#define PSR_MODE_EL2t	0x00000008
#define PSR_MODE_EL2h	0x00000009
#define PSR_MODE_EL3t	0x0000000c
#define PSR_MODE_EL3h	0x0000000d


/*
 * Task registers (?)
 * Should be in the exact same order as stored by the store_registers macro
 * when doing a context switch
 */
typedef struct {
	uint64_t regs[31];	// x0 - x30 (?)
	uint64_t sp;		// Stack pointer
	uint64_t pc;		// Program counter (elr_el1)
	uint64_t pstate;	// Process state (spsr_el1)
} pt_regs_t;


/*
 * Function definitions
 */
int32_t create_process(uint64_t clone_flags, uint64_t func_pointer, uint64_t arg, uint64_t stack);
extern void ret_from_fork();
int8_t  move_to_user(uint64_t);
pt_regs_t *task_pt_regs(task_t*);


#endif /* FORK_H */
