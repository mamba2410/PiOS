# TODO

- Change mailboxes to use bit fields
- Add full UART port
	- Think theres something up with the baud rate
- Implement `sprintf`
- Change exception level to EL1
	- Need to fix exception level, currently running at EL2, need EL3
- Change `mmio_xxx` to a macro?
	- Constant addresses look like `#define ADDRESS (uint64_t*)(0x00000)`
	- Macro looks like `#define MMIO_PUT32(address, data) *(ADDRESS) = data`
	- Similarly for `get32``#define MMIO_GET32(address) *(ADDRESS)`
	- Delay looks like `#define MMIO_DELAY(count) while(count--){asm volatile("nop");}`
- Research and implement interrupt handling
- Research and implement memory paging

