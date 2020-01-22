#ifndef MEM_H
#define MEM_H

#include <addresses/mmio_base.h>

// Define pages as being 2^12 bytes(?) long
// Corresponds to 4K
#define PAGE_SHIFT		12
// Define tables as being 2^9 bytes(?) long
// Corresponds to 512B
#define TABLE_SHIFT		9
// Define the section size to be 21 bytes(?) long
// Corresponds to 2M
#define SECTION_SHIFT 	(PAGE_SHIFT + TABLE_SHIFT)

// Set the page size to 4K
#define PAGE_SIZE		(1<<PAGE_SHIFT)
// Set the section size to 2M
#define	SECTION_SIZE	(1<<SECTION_SHIFT)

// Define low memory constant to 2 sections
// Corresponds to 4M
// This is actually the amount of bytes allocated to the kernel
#define LOW_MEMORY		(2*SECTION_SIZE)

// Define high memory constant, above this is where MMIO registers are
#define HIGH_MEMORY		MMIO_BASE

// Define the amount of memory available for paging
#define PAGING_MEMORY	(HIGH_MEMORY - LOW_MEMORY)
// Define the number of pages that can be used for paging
#define PAGING_PAGES	(PAGING_MEMORY/PAGE_SIZE)


/*
 * Function definitions
 */
#ifndef __ASSEMBLER__

uint64_t	get_page();
void		free_page(uint64_t);
void		zero_memory(uint64_t src, uint64_t n);

#endif

#endif /* MEM_H */
