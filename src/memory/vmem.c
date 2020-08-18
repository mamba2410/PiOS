#include <addresses/vmem.h>
#include <memory/mem.h>
#include <memory/vmem.h>
#include <proc/tasks.h>
#include <mmu.h>


/*
 *	Map a page to a virtual address for a certain task
 *	Only needed for user tasks since kernel memory is already mapped out
 */
void map_page(task_t *task, uint64_t va, uint64_t page) {
	uint64_t table;
	int8_t new_table;
	if(!task->mm.pgd) {					// Do we already have a PGD for this task?
		task->mm.pgd = get_page();		// If not, make one and keep track of the page
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = task->mm.pgd;
		printf("[D] Making new PGD(%08x)\n", task->mm.pgd);
	}


	table = task->mm.pgd;				// Set the current table to the task's PGD

	// PGD -> PUD
	table = map_table( (uint64_t*)(table+VA_START), PGD_SHIFT, va, &new_table );	// Get addr of va's PUD
	if(new_table) task->mm.kernel_pages[++task->mm.kernel_pages_count] = table;		// If we made a new table, keep track
	
	// PUD -> PMD
	table = map_table( (uint64_t*)(table+VA_START), PUD_SHIFT, va, &new_table );	// Get addr of va's PMD
	if(new_table) task->mm.kernel_pages[++task->mm.kernel_pages_count] = table;		// If we made a new table, keep track

	// PMD -> PTE
	table = map_table( (uint64_t*)(table+VA_START), PMD_SHIFT, va, &new_table );	// Get addr of va's PTE
	if(new_table) task->mm.kernel_pages[++task->mm.kernel_pages_count] = table;		// If we made a new table, keep track

	map_table_entry( (uint64_t*)(table+VA_START), va, page );	// Actually put the page descriptor in
	user_page_t p = {.phys_addr=page, .virt_addr=va};									// Add this page to the task struct
	printf("[D] Mapping page %08x->%08x\n", page, va);
	task->mm.user_pages[task->mm.user_pages_count++] = p;
}


/*
 *	Return physical address of table that holds the given va
 *	Make a new table if one does not exist
 */
uint64_t map_table(uint64_t *table, uint64_t shift, uint64_t va, int8_t *new_table) {
	uint64_t index = (va>>shift) & (DESCRIPTORS_PER_TABLE-1);		// Get index of va in the table
	*new_table = 0;													// So far, no new table
	if(!table[index]) {												// Is there already a descriptor?
		*new_table = 1;												// If not, set the flag
		uint64_t next_table = get_page();							// and make one
		table[index] = next_table | MM_TYPE_PAGE_TABLE;				// Set the descriptor
	}

	return table[index] & PAGE_MASK;								// Return the table address
}

/*
 *	Adds a physical address descriptor to the PTE for a given va
 */
void map_table_entry(uint64_t *pte, uint64_t va, uint64_t pa) {
	uint64_t index = (va>>PAGE_SHIFT) & (DESCRIPTORS_PER_TABLE-1);		// Get index of va in the table
	pte[index] = pa | MMU_PTE_FLAGS;								// Write the physical address and set flags
}


/*
 *	Copy virtual memory from current task to 
 *	new user task. Allocate new page if one doesn't exist
 */
int32_t copy_virt_memory(task_t *dst) {
	task_t *src = current_task;
	for (uint32_t i = 0; i < src->mm.user_pages_count; i++) {
		uint64_t kernel_va = allocate_user_page(dst, src->mm.user_pages[i].virt_addr);
		if(!kernel_va) return -1;
		memcpy(kernel_va, src->mm.user_pages[i].virt_addr, PAGE_SIZE);
	}
	return 0;
}


/*
 *	Handle a memory abort exception, need a global incrementer because?
 */
static uint64_t g_ind = 1;
int32_t _mem_abort(uint64_t addr, uint64_t esr) {
	uint64_t dfs = esr&0x3F;			// Get the bits we care about in the esr
	if((dfs&0x3C) == 0b100) {			// Are we the right data abort? (translation fault)
		uint64_t page = get_page();		// If so, get a new page
		if(!page) return -1;			// (and check to see if successful)

		map_page(current_task, addr&PAGE_MASK, page);	// Map the new page to the virtual address
		g_ind++;						// Increment a global variable
		if(g_ind>2) return -1;			// Fail if this happens too much?
		return 0;
	}
	return -1;							// If we aren't a translation fault, throw error
}
