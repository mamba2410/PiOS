
/*
 *	Set the user task PGD
 *	I don't really know what this is doing after the set 
 */
.global set_pgd
set_pgd:
	msr		ttbr0_el1, x0	// Put the table address into the register
	tlbi	vmalle1is		// Invalidate all TLB caches
	DSB		ISH				// Ensure completion of TLB invalidation
	isb						// ???
	ret						// Return


/*
 *	I have no idea what this is doing
 */
.global get_pgd
get_pgd:
	mov		x1, 0
	ldr		x0, [x1]
	mov		x0, 0x1000
	msr		ttbr0_el1, x0
	ldr		x0, [x1]
	ret

