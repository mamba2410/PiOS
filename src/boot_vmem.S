#include <addresses/vmem.h>
#include <addresses/addr_base.h>
#include <memory/mem.h>
#include <mmu.h>

.section ".text.boot"

.macro create_table_entry, tbl, virt, shift, offset, tmp1, tmp2
	lsr		\tmp1, \virt, #\shift						// Get the page index from the va
	and		\tmp1, \tmp1, #DESCRIPTORS_PER_TABLE-1		// Clear the top bits of the index
	add		\tmp2, \tbl, #\offset						// Get address of next table to map
	orr		\tmp2, \tmp2, #MM_TYPE_PAGE_TABLE			// Set lower bits to a table descriptor
	str		\tmp2, [\tbl, \tmp1, lsl #3]				// Store address of next table in first table
	//add		\tbl, \tbl, #PAGE_SIZE						// Set table pointer to next table
.endm													// Ready to be called again


.macro create_block_map, tbl, phys, start, end, flags, tmp1
	lsr		\start, \start, #SECTION_SHIFT
	and		\start, \start, #DESCRIPTORS_PER_TABLE-1	// Get PMD table index of start va
	lsr		\end, \end, #SECTION_SHIFT
	and		\end, \end, #DESCRIPTORS_PER_TABLE-1		// Get PMD table index of end va
	lsr		\phys, \phys, #SECTION_SHIFT				// Get PMD table index of physical section
	mov		\tmp1, #\flags								// Load descriptor flags
	orr		\phys, \tmp1, \phys, lsl #SECTION_SHIFT		// Shift back and or-in the descriptor flags
9999:
	str		\phys, [\tbl, \start, lsl #3]				// Store the descriptor
	add		\start, \start, #1							// Increment table index
	add		\phys, \phys, #SECTION_SIZE					// Increment descriptor
	cmp		\start, \end								// 
	b.ls	9999b										// Repeat until we are at the end address
.endm

.global _create_kernel_tables
_create_kernel_tables:
	mov		x29, x30			// Save link register
	adrp	x0, __k_pages_start	// Load start address of kernel page tables
	adrp	x1, __k_pages_end	// Load the end address of kernel page tables
	sub		x1, x1, x0			// Get the size of the pages
	bl		zero_memory			// Zero the tables
	adrp	x0, __k_pages_start	// Load kernel table address
	mov		x1, #VA_START		// Load virtual memory start address
	create_table_entry x0, x1, PGD_SHIFT, PAGE_SIZE, x3, x4	// Create the PGD table for the kernel
	add		x0, x0, #PAGE_SIZE								// Get address of the PUD
	create_table_entry x0, x1, PUD_SHIFT, PAGE_SIZE, x3, x4	// Create the PUD table for the kernel
	ldr		x1, =LOCAL_BASE									// Load the VA of the local peripherals
	create_table_entry x0, x1, PUD_SHIFT, (2*PAGE_SIZE), x3, x4	// Map the second PMD
	add		x0, x0, #PAGE_SIZE									// Get address of first PMD
	/* Map available memory as normal, non-cacheable*/
	mov		x1, xzr												// Map phys addr 0
	mov		x2, #VA_START										// to virt addr 0
	ldr		x3, =( MMIO_BASE - SECTION_SIZE )					// for all memory until device registers
	create_block_map x0, x1, x2, x3, MMU_NNC_FLAGS, x4			// Map available mem as sections in the PMD
	/* Map device memory as devices */
	mov		x1, #MMIO_BASE_PHYS									// Map phys addr mmio_base
	ldr		x2, =MMIO_BASE										// to virt addr mmio_base	
	ldr		x3, =( LOCAL_BASE - SECTION_SIZE )					// until the end of the GPU address space (1GB)
	create_block_map x0, x1, x2, x3, MMU_DEVICE_FLAGS, x4		//

	add		x0, x0, #PAGE_SIZE									// Get address of second PMD
	mov		x1, #LOCAL_BASE_PHYS								// Now we map the local base (1GB)
	ldr		x2, =LOCAL_BASE										// to its virtual counterpart
	ldr		x3, =( LOCAL_END - SECTION_SIZE )					// until the end of the device maps
	create_block_map x0, x1, x2, x3, MMU_DEVICE_FLAGS, x4		//

	mov		x30, x29			// Restore the return address
	ret							// gtfo
