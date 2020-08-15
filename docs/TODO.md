# TODO

## Bugfixes
None that I'm aware of

## Frontburner
- Rework linker script to be better
	- Linker tokens `__SECTION_start` and `__SECTION_end` should exist for all sections
	- Have a different one for vmem, pmem, etc.
- Change directory structure.
	- `Makefile` top level
	- Rename `bin` to `build`
	- Build should contain all things needed to build - except for `Makefile`. This includes metadata about the build process etc.
	- Binary files should be in `build/target/`
- Virtual memory

## Exercises
- 04/2 - Allow task max lifetimes to change on init.
- 04/4 - Allow unlimited number of tasks.


## Tests
- Print memory map when tasks switch etc. Make sure sp etc are in the right place.


## Features/Research
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
- Mailboxes, how they work, how to interact etc
- Different scheduler types
	- Round robin
	- Completely Fair Scheduler (CFS)
	- Most needed etc
- Filesystems
	- [FAT32](https://github.com/bztsrc/raspi3-tutorial/tree/master/0C_directory)
	- ext4


