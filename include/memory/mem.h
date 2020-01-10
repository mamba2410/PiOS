#ifndef MEM_H
#define MEM_H

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
#define PAGE_SIZE		1<<PAGE_SHIFT
// Set the section size to 2M
#define	SECTION_SIZE	1<<SECTION_SHIFT

// Define low memory variable to 2 sections
// Corresponds to 4M
// This is actually the amount of bytes allocated to the kernel
#define LOW_MEMORY		2*SECTION_SIZE


#ifndef __ASSEMBLER__
// Declare a C function prototype to clear the memory
void zero_memory(unsigned long src, unsigned long n);
#endif

#endif
