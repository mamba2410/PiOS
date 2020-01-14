# TODO

## Bugfixes
- Add full UART port
	- Think theres something up with the baud rate
- Move all addresses in headers to `addresses/<thing>.h` with `#ifndef ADDR_THING_H`

## Features
- Interrupts
	- Put interrupt polling in a loop, multiple interrupts could come at once
	- Give unhandled interrupts better messages
- Implement `sprintf`
- Implement a memory address type `typedef phys_addr_t uint64_t*;` for memory address pointers.

## Optimisation
- Change `mmio_get32()` and `mmio_put32()` to be more efficient.
- Change mailboxes to use bit fields

## Research
- Research and implement memory paging

