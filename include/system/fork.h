#ifndef FORK_H
#define FORK_H

#include <stdint.h>

/*
 * Function definitions
 */
uint8_t create_process(uint64_t clone_flags, uint64_t func_pointer, uint64_t arg, uint64_t stack);
extern void ret_from_fork();

/*
 * Task registers (?)
 */
typedef struct {
	uint64_t regs[31];	// x0 - x30 (?)
	uint64_t sp;		// Stack pointer
	uint64_t pc;		// Program counter
	uint64_t pstate;	// Process state
} pt_regs_t;


#endif /* FORK_H */
