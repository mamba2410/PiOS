#include <memory/mem.h>
#include <memory/vmem.h>
#include <stdint.h>

/*
 * Map of all pages, page is either allocated (1) or not allocated (0)
 */
static uint8_t page_map [ PAGING_PAGES ] = {0};


/*
 * Returns the physical memory address of a page
 */
uint64_t get_page(){
	for(int32_t i = 0; i < PAGING_PAGES; i++){	// Loop through all available pages
		if( !(page_map[i]) ){					// If page is not allocated
			page_map[i] = 1;					// mark page as allocated
			uint64_t page = LOW_MEMORY + i*PAGE_SIZE;	// Return address of that page
			zero_memory(page + VA_START, PAGE_SIZE);	// Zero the page
			return page;								// Return the physical address
		}
	}
	return 0;									// If something went wrong, return 0
}

/*
 *	Return memory address of page in kernel mem space
 */
uint64_t allocate_kernel_page() {
	uint64_t p = get_page();
	if(!p) return 0;
	return p + VA_START;
}

/*
 *	Return memory address of page in kernel space
 *	that has been mapped to a virtual address
 */
uint64_t allocate_user_page(task_t *task, uint64_t va) {
	uint64_t p = get_page();
	if(!p) return 0;
	map_page(task, va, p);
	return p + VA_START;
}

/*
 * Free a page for use again
 */
void free_page(uint64_t page){
	page_map[ (page-LOW_MEMORY)/PAGE_SIZE ] = 0;	// Set page as unallocated
}

