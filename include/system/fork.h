#ifndef FORK_H
#define FORK_H

#include <system/tasks.h>

/*
 * Function definitions
 */
uint8_t create_process(uint64_t func_pointer, uint64_t arg);
extern void ret_from_fork();


#endif /* FORK_H */
