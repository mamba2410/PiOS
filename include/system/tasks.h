#ifndef TASKS_H
#define TASKS_H

#include <stdint.h>

/*
 * CPU Context struct
 * Store the upper registers, as well as stack pointer, program counter
 * and fp.
 * x0-x18 are not expected to remain intact after calling a function
 * Context will only switch if the process calls a function, so it should
 * not expect the registers to stay intact
 *
 * Context switches will only happen when a function is called, if the task
 * calls the function then it knows to not expect registers to stay intact
 * if it is called from an interrupt, then all the registers are already saved
 * in the interrupt macro
 */
typedef struct {
	uint64_t x19;
	uint64_t x20;
	uint64_t x21;
	uint64_t x22;
	uint64_t x23;
	uint64_t x24;
	uint64_t x25;
	uint64_t x26;
	uint64_t x27;
	uint64_t x28;
	uint64_t fp;	// x29, frame pointer
	uint64_t pc;	// x30, program counter / link register
	uint64_t sp;	//		stack pointer
} cpu_context_t;

/*
 * Struct for a task
 * Stores the cpu context for the task, 
 * the state the task is in,
 * a counter for the lifetime of the task, how many timeslices it has before it can be switched
 * a counter for the lifetime that the task cannot be switched
 * the priority of the task, a measure of how long the task can last
 */
typedef struct {
	cpu_context_t cpu_context;
	int64_t state;
	int64_t lifetime;
	int8_t  can_preempt;
	int64_t priority;
} task_t;


/*
 * Task states
 */
#define TASK_STATE_HALTED	0
#define TASK_STATE_RUNNING	1
#define TASK_STATE_WAITING_INTERRUPT	2


/*
 * Maximum number of tasks available
 */
#define MAX_TASKS 64


/*
 * Init task struct
 * All registers are zero, task is running, task has no lifetime left, can preempt, priority 1
 */
#define INIT_TASK_STRUCT { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, \
							TASK_STATE_RUNNING, 0, 1, 1 }

/*
 * Declare that these variables are declared somewhere else
 */
extern task_t *current_task;
extern task_t *tasks[MAX_TASKS];
extern uint32_t number_tasks;


/*
 * Function definitions
 */
void preempt_enable();
void preempt_disable();
void schedule();
void schedule_tick();
void switch_task(task_t*);
extern void cpu_switch_task(task_t*, task_t*);


#endif /* TASKS_H */
