# TODO

## Bugfixes
- Have a ladder to branch to EL1 from whatever exception level it was booted in, only drop one level at a time
- Get context switching to work
	- System timer only appears to execute once, then never again
	- Probably something to do with interrupts not saving the right registers or saving in the right place, check out the vector tables and `kernel_entry` and `kernel_exit`
- Add full UART port
	- Think theres something up with the baud rate
- Move all addresses in headers to `addresses/<thing>.h` with `#ifndef ADDR_THING_H`
- Get things to link with static libraries

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

