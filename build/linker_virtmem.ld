
/*
 * Define the sections in this object
 */
SECTIONS{
	/*
	 * Code is loaded at physical offset 0x80000
	 * Since we are using virtual memory, the kernel
	 * thinks we are 0xFFFF000000000000 ahead of 0x00
	 */
	. = 0xFFFF000000080000;

	/* Have a boot section for boot code. */
	__text_boot_start = .;
	.text.boot	: { *(.text.boot) }
	__text_boot_end = .;

	/*
	 *	For now, a hack to get the user code separate to the kernel code
	 *	Later, this will be a separate executable
	 */
	. = ALIGN(0x00001000);
	__user_start = .;
	.text.user		: { *user* (.text) }
	.rodata.user	: { *user* (.rodata) }
	.data.user		: { *user* (.data) }
	.bss.user		: { *user* (.bss) }
	__user_end = .;

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


	/* Align to the next 4k, start of kernel page tables */
	. = ALIGN(0x00001000);

	/*
	 *	Allocate 4x4k pages inside the kernel image
	 *	Save the start and size of the section
	 */
	__k_pages_start = .;
	.data.pgd	: { . += (4 * (1 << 12)); }
	__k_pages_end = .;
	__k_pages_size = __k_pages_end - __k_pages_start;
}
