#ifndef MEM_H
#define MEM_H

#include <addresses/addr_base.h>

#define PAGE_SHIFT		12			// Each page is 1<<12 (4K) bytes
#define TABLE_SHIFT		9			// Each table holds 1<<9 (512) descriptors
#define SECTION_SHIFT 	(PAGE_SHIFT + TABLE_SHIFT)	// Each section is 1<<(12+9) (2M) bytes

#define PGD_SHIFT		(PAGE_SHIFT + 3*TABLE_SHIFT)
#define PUD_SHIFT		(PAGE_SHIFT + 2*TABLE_SHIFT)
#define PMD_SHIFT		(PAGE_SHIFT + 1*TABLE_SHIFT)
#define KERNEL_PAGES_SIZE	(3*(1<<12))

#define PAGE_SIZE		(1<<PAGE_SHIFT)		// Page size is 4K
#define	SECTION_SIZE	(1<<SECTION_SHIFT)	// Section size is 2M

#define DESCRIPTORS_PER_TABLE	(1<<TABLE_SHIFT)	// We have 512 descriptors in each table

#define LOW_MEMORY		(2*SECTION_SIZE)	// Where we stop the kernel memory and make it general memory (4M bytes)
#define HIGH_MEMORY		MMIO_BASE_PHYS		// Above here is off-limits, it is mmio registers

#define PHYS_MEM_SIZE	0x40000000			// 1G of memory

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

#endif /* __ASSEMBLER__ */


#endif /* MEM_H */
