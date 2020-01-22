#include <system/fork.h>
#include <system/tasks.h>
#include <memory/mem.h>


/*
 * Prepares a new task and adds it to the processes array
 * Does not perform a context switch, only makes a task
 */
uint8_t create_process(uint64_t func, uint64_t arg){
	preempt_disable();

	task_t *page;

	page = (task_t*)get_page();			// Get a page for the new process
	if( !page ) return 1;				// If no page was found

	page->priority = current_task->priority;	// Set priority, lifetime etc
	page->state = TASK_STATE_RUNNING;
	page->lifetime = page->priority;
	page->can_preempt = 0;

	page->cpu_context.x19 = func;		// Set registers for the task
	page->cpu_context.x20 = arg;
	page->cpu_context.pc  = (uint64_t)ret_from_fork;
	page->cpu_context.sp  = ((uint64_t)page + PAGE_SIZE);

	tasks[ number_tasks++ ] = page;		// Put this task in the array and increment the number

	preempt_enable();
	return 0;
}
