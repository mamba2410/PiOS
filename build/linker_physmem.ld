
/*
 * Define the sections in this object
 */
SECTIONS{
	/* Code is loaded at 0x80000 */
	. = 0x80000;	

	/* Have a boot section for boot code. */
	__text_boot_start = .;
	.text.boot	: { *(.text.boot) }
	__text_boot_end = .;

	/* Have a general code section */
	__text_start = .;
	.text		: { *(.text) }
	__text_end = .;

	/* Read-only initialised data. Constants(?) */
	__rodata_start = .;
	.rodata		: { *(.rodata) }
	__rodata_end = .;

	/* Variable initialised data */
	__data_start = .;
	.data		: { *(.data) }
	__data_end = .;

	/* 
	 * Align to the next 8 bytes
	 * Needed in order for pi to be able to do something
	 */
	. = ALIGN(0x8);
	/*
	 * Uninitialised data goes here
	 * This is where all variables can be stored
	 */
	__bss_start	= .;
	.bss		: { *(.bss) }
	__bss_end = .;
}
