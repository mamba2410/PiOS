#ifndef MEM_H
#define MEM_H

#include <addresses/addr_base.h>

#define PAGE_SHIFT		12			// Each page is 1<<12 (4K) bytes
#define TABLE_SHIFT		9			// Each table is 1<<5 (512) bytes
#define SECTION_SHIFT 	(PAGE_SHIFT + TABLE_SHIFT)	// Each section is 1<<(12+9) (2M) bytes

#define PAGE_SIZE		(1<<PAGE_SHIFT)		// Page size is 4K
#define	SECTION_SIZE	(1<<SECTION_SHIFT)	// Section size is 2M

#define LOW_MEMORY		(2*SECTION_SIZE)	// Where we stop the kernel memory and make it general memory (4M bytes)
#define HIGH_MEMORY		MMIO_BASE			// Above here is off-limits, it is mmio registers

#define PAGING_MEMORY	(HIGH_MEMORY - LOW_MEMORY)	// Number of bytes available for memory paging
#define PAGING_PAGES	(PAGING_MEMORY/PAGE_SIZE)	// Number of pages available

/*
 * C stuff
 */
#ifndef __ASSEMBLER__

#include <stdint.h>

uint64_t	get_page();
void		free_page(uint64_t);
void		zero_memory(uint64_t src, uint64_t n);

#endif /* __ASSEMBLER */


#endif /* MEM_H */
