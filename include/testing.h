#ifndef TESTING_H
#define TESTING_H

#include <stdint.h>

void testing_process();

void example_process(char*);
void user_process();
void kernel_process();

extern uint64_t get_exception_level();
extern uint32_t number_tasks;

#endif /* TESTING_H */
