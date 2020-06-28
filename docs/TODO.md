# TODO

## Bugfixes
None that I'm aware of

## Exercises
- 02/2 - Use `cpacr_el1` to enable FP/SIMD registers and remove `-mgeneral-regs-only` flag from compilation. Store these on interrupts etc.
- 03/1 - Allow use of local timer for timer interrupts.
- 03/2 - Handle UART and miniUART interrupts, test with echo.
- 04/2 - Allow task max lifetimes to change on init.
- 04/4 - Allow unlimited number of tasks.


## Tests
- Print memory map when tasks switch etc. Make sure sp etc are in the right place.


## Features
- User processes
	- `fork` `kfork` `clone` `kclone` etc
- Virtual memory
	- [btzsrc](https://github.com/bztsrc/raspi3-tutorial/tree/master/10_virtualmemory)
	- s-matyukevitch, lesson 06
- Rewrite mailbox code to be better
- Random numbers
	- Pseudo-random
	- Hardware backed?	
- `delay_millis()` `delay_micros()` functions
	- delay doesn't seem too accurate, currently using system timer which apparently uses clock cycles
	- Create `wait_*()` functions that schedule and wait for interrupts, like timer etc
- [Power managment](https://github.com/bztsrc/raspi3-tutorial/blob/master/08_power/power.c)
	- Shutdown the pi
	- Reboot the pi
	- Maybe get an echo loop, if input `r` and `h` in serial, reset and halt
- Change schedule function at compilation
	- Configs like `SCHEDULER_CFS` and `SCHEDULER_RR` etc

## Optimisation
- Change `mmio_get32()` and `mmio_put32()` to be more efficient.
- Change mailboxes to use bit fields
	- Mailboxes should just be better implemented in general

## Research
- Mailboxes, how they work, how to interact etc
- Different scheduler types
	- Round robin
	- Completely Fair Scheduler (CFS)
	- Most needed etc
- Filesystems
	- [FAT32](https://github.com/bztsrc/raspi3-tutorial/tree/master/0C_directory)
	- ext4
