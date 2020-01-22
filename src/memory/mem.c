#include <memory/mem.h>
#include <stdint.h>

/*
 * Map of all pages, page is either allocated (1) or not allocated (0)
 */
static uint8_t page_map [ PAGING_PAGES ] = {0};


/*
 * Returns the memory address of a page
 */
uint64_t get_page(){
	for(uint32_t i = 0; i < PAGING_PAGES; i++){	// Loop through all available pages
		if( !(page_map[i]) ){					// If page is not allocated
			page_map[i] = 1;					// mark page as allocated
			return LOW_MEMORY + i*PAGE_SIZE;	// Return address of that page
		}
	}
	return 0;									// If something went wrong, return 0
}

/*
 * Free a page for use again
 */
void free_page(uint64_t page){
	page_map[ (page-LOW_MEMORY)/PAGE_SIZE ] = 0;	// Set page as unallocated
}

