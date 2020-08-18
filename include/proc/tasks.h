#ifndef TASKS_H
#define TASKS_H

#define CPU_CONTEXT_OFFSET		0x000		// cpu_context is the first member of task_t, so has no offset
#define FPSIMD_CONTEXT_OFFSET	0x070		// fpsimd_context is after cpu_context which is 0x70 bytes 
#define STATE_OFFSET			0x280		// state offset in task_t


#ifndef __ASSEMBLER__
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
	union{ uint64_t x29; uint64_t fp; };	// x29/frame pointer
	union{ uint64_t x30; uint64_t pc; };	// x30/program counter
	uint64_t sp;							// stack pointer
} cpu_context_t;

/*
 * FP/SIMD context struct
 * Store all SIMD registers (which are 128 bits wide) as well as the 
 * control and status registers.
 * I an unsure why we save these here and not on an interrupt. Are these
 * expected to not be modified when a context switch occurs?
 */
typedef struct {
	__uint128_t vregs[32];
	uint32_t fpsr;
	uint32_t fpcr;
} fpsimd_context_t;


/*
 * Structure to keep track of pages for a user task
 * Holds both the virtual address, as used by the task
 * as well as the physical address
 */
typedef struct {
	uint64_t phys_addr;
	uint64_t virt_addr;
} user_page_t;

/*
 * Maximum number of pages a task can have
 */
#define MAX_PROCESS_PAGES	16

/*
 * Struct to keep track of memory for a task
 * Keeps track of the PGD and any pages it has allocated for it
 */
typedef struct {
	uint64_t	pgd;
	uint16_t	user_pages_count;
	user_page_t	user_pages[ MAX_PROCESS_PAGES ];
	uint16_t	kernel_pages_count;
	uint64_t	kernel_pages[ MAX_PROCESS_PAGES ];
} mm_t;

/*
 * Struct for a task
 * Stores the cpu context for the task, 
 * the state the task is in,
 * a counter for the lifetime of the task, how many timeslices it has before it can be switched
 * a counter for the lifetime that the task cannot be switched
 * the priority of the task, a measure of how long the task can last
 */
typedef struct {
	cpu_context_t		cpu_context;
	fpsimd_context_t	fpsimd_context;
	int64_t		state;
	int64_t		lifetime;
	int64_t		can_preempt;
	int64_t		priority;
	uint64_t	stack;
	uint64_t	flags;
	mm_t		mm;
} task_t;

// Init task definition
#define INIT_CPU_CONTEXT_STRUCT {.x19=0, .x20=0, .x21=0, .x22=0, .x23=0, .x24=0, .x25=0, .x26=0, .x27=0, .x28=0, .fp=0, .pc=0, .sp=0}
#define INIT_MM_STRUCT { 0, 0, {{0}}, 0, {0}}
#define INIT_TASK_STRUCT {	.cpu_context	= INIT_CPU_CONTEXT_STRUCT,\
							.state			= TASK_STATE_RUNNING,\
							.lifetime		= 0,\
							.can_preempt	= 1,\
							.priority		= 1,\
							.stack			= 0,\
							.flags			= PF_KERNEL_THREAD,\
							.mm				= INIT_MM_STRUCT}


// Task states
#define TASK_STATE_HALTED				0
#define TASK_STATE_RUNNING				1
#define TASK_STATE_WAITING_INTERRUPT	2
#define TASK_STATE_ZOMBIE				3

/*
 * Clone flag constants
 */
#define PF_KERNEL_THREAD				0x00000002

#define MAX_TASKS 64	// Maximum number of tasks can handle

// Declare these global variables
extern task_t *current_task;
extern task_t *tasks[MAX_TASKS];
extern uint32_t number_tasks;

void preempt_enable();
void preempt_disable();
void schedule();
void schedule_tick();
void switch_task(task_t*);
void exit_process();
extern void cpu_switch_task(task_t*, task_t*);

#endif /* __ASSEMBLER */

#endif /* TASKS_H */
