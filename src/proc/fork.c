#include <stdint.h>
#include <memory/mem.h>
#include <proc/fork.h>
#include <proc/tasks.h>

/*
 * Prepares a new task and adds it to the processes array
 * Does not perform a context switch, only makes a task
 */
int32_t create_process(uint64_t clone_flags, uint64_t func, uint64_t arg, uint64_t sp){
	preempt_disable();		// Cannot switch tasks whilst making a new task

	task_t *page;
	page = (task_t*)get_page();			// Get a page for the new process
	if( !page ) return 1;				// If no page was found

	pt_regs_t *child_regs = task_pt_regs(page);						// Get pointer to saved task registers 
	zero_memory((uint64_t)child_regs, sizeof(pt_regs_t));				// Zero out the registers
	zero_memory((uint64_t)&(page->cpu_context), sizeof(cpu_context_t));// Zero out the cpu context

	if( clone_flags & PF_KERNEL_THREAD ){							// If we are a kernel thread
		page->cpu_context.x19 = func;								// Load registers with function
		page->cpu_context.x20 = arg;								// and argument
	} else{															// If we are a user thread
		pt_regs_t *current_regs = task_pt_regs(current_task);		// Get the current task registers
		*child_regs = *current_regs;								// Copy them to the child
		child_regs->regs[0] = 0;									// Set x0 to zero (so we know it's the child)
		child_regs->sp = sp + PAGE_SIZE;							// Save child stack top as sp
		page->stack = sp;											// Save child stack bottom
	}

	page->flags = clone_flags;					// Copy over clone flags
	page->priority = current_task->priority;	// Set priority, lifetime etc
	page->state = TASK_STATE_RUNNING;			//
	page->lifetime = page->priority;			//
	page->can_preempt = 0;						//

	page->cpu_context.pc  = (uint64_t)ret_from_fork;	// Set child process pc to the proper function
	page->cpu_context.sp  = (uint64_t)child_regs;		// Set child stack pointer to just below its saved registers

	int32_t pid = number_tasks++;	// Get the PID of the child task
	tasks[pid] = page;				// Put child task in the global array

	preempt_enable();				// Done making a new task, can switch now
	return pid;						// Return child process ID
}


/*
 * Move a task to user mode in EL0
 */
int8_t move_to_user(uint64_t pc){
	pt_regs_t *r = task_pt_regs(current_task);	// Get processor registers of current task
	zero_memory((uint64_t)r, sizeof(*r));			// Zero them out
	r->pc = pc;									// Set pc to function argument
	r->pstate = PSR_MODE_EL0t;					// Set program state to EL0t
	uint64_t sp = get_page();					// Get a new memory page
	if(!sp) return -1;							// If failed, return -1
	r->sp = sp + PAGE_SIZE;						// If not, set current task sp register to top of page
	current_task->stack = sp;					// Set task_t stack pointer to bottom of page
	return 0;									// Return OK
}

/*
 * Get registers from task
 */
pt_regs_t* task_pt_regs(task_t *task){
	uint64_t r = (uint64_t)task + PAGE_SIZE - sizeof(pt_regs_t);	// Calculate address of saved registers in memory
	return (pt_regs_t*)r;											// Return as a pointer to a pt_regs_t
}
