#include <memory/mem.h>

// Tells the linker to put everything here in the .text.boot section
.section ".text.boot"
// Tells the assembler that _start should be visible anywhere
.global _start

// Note: x<n> is a 64-bit register
//		w<n> is the lower 32-bits of x<n>

// This code is run by all processor cores. Multi-core processors are hard so
// just infi-loop all processors except id 0
_start:
	// mrs loads a value from system register and puts it into general purpose register
	// x0 is first general purpose register
	// mpdir_el1 is the system register that holds the processor id
	mrs	x0, mpidr_el1
	// Test the last byte of the processor id
	// Really just a way of putting the last byte of the id into the compare register
	and	x0,	x0,	#0xff
	// If processor id is zero, go to master label
	cbz	x0,	master
	// If processor id is not zero, branch to infinite loop
	b	processor_hang

// Infi-loop to hang the processors we don't want
processor_hang:
	b	processor_hang

// master label, branched to by processor we want
master:
	// Load the bss_begin address into x0
	adr	x0,	bss_begin
	// Load the bss_end address into x1
	adr x1,	bss_end
	// Get the size of the bss region and put in x1
	sub	x1,	x1,	x0
	// Branch with link (remember where you came from) to the zero_memory label
	bl	zero_memory
	
	// Move stack pointer to this address
	// Stack pointer moves down from here to zero
	// Reccommended by github is 4M, as kernel is tiny
	mov	sp,	#LOW_MEMORY
	// Branch to function called kernel_main
	// This will be defined in a c file
	bl	kernel_main

	// When done, just chill I guess
	// Should probably terminate with something here.


