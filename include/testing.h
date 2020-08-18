#ifndef TESTING_H
#define TESTING_H

#include <stdint.h>

void testing_main();

void kernel_process();

extern uint64_t get_exception_level();
extern uint32_t number_tasks;

extern uint64_t __user_start;
extern uint64_t __user_end;

extern uint64_t get_q0();
extern uint64_t get_q2();
extern uint64_t get_q31();
extern void set_q0(uint64_t);
extern void set_q2(uint64_t);
extern void set_q31(uint64_t);

#endif /* TESTING_H */
