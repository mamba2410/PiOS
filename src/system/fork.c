#include <stdint.h>
#include <memory/mem.h>
#include <system/fork.h>
#include <system/tasks.h>

/*
 * Prepares a new task and adds it to the processes array
 * Does not perform a context switch, only makes a task
 */
uint8_t create_process(uint64_t func, uint64_t arg){
	preempt_disable();		// Cannot switch tasks whilst making a new task

	task_t *page;
	page = (task_t*)get_page();			// Get a page for the new process
	if( !page ) return 1;				// If no page was found

	page->priority = current_task->priority;	// Set priority, lifetime etc
	page->state = TASK_STATE_RUNNING;			//
	page->lifetime = page->priority;			//
	page->can_preempt = 0;						//

	page->cpu_context.x19 = func;						// Set registers for the task
	page->cpu_context.x20 = arg;						//
	page->cpu_context.pc  = (uint64_t)ret_from_fork;	//
	page->cpu_context.sp  = (uint64_t)page + PAGE_SIZE;	//

	tasks[ number_tasks++ ] = page;		// Put this task in the array and increment the number

	preempt_enable();	// Done making a new task, can switch now
	return 0;
}


/*
 * Move a task to user mode in EL0
 */
int8_t move_to_user(uint64_t pc){
	pt_regs_t *r = task_pt_regs(current);
}

/*
 * Get registers from task
 */
pt_regs_t* task_pt_regs(task_t *task){
	uint64_t r = (uint64_t)task + PAGE_SIZE - sizeof(pt_regs_t);
	return (pt_regs_t*)r;
}
