
/*
 * Define the sections in this object
 */
SECTIONS{
	/* Have a boot section for boot code. */
	.text.boot	: { *(.text.boot) }
	/* Have a general code section */
	.text		: { *(.text) }
	/* Read-only initialised data. Constants(?) */
	.rodata		: { *(.rodata) }
	/* Variable initialised data */
	.data		: { *(.data) }

	/* Align to the next 8 bytes
	 * Needed in order for pi to be able to do something
	 */
	. = ALIGN(0x8);
	/* Record where the bss section begins
	 * This is because we need to zero out the .bss section of the 
	 * Memory otherwise bad things can happen
	 */
	bss_begin	= .;
	/* Uninitialised data goes here
	 * This is where all variables can be stored
	 */
	.bss		: { *(.bss) }
	/* Record where the bss stops */
	bss_end		= .;
}
