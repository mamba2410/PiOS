# TODO

## Bugfixes

## Features
- User processes
	- `fork` `kfork` `clone` `kclone` etc
- Virtual memory
	- [btzsrc](https://github.com/bztsrc/raspi3-tutorial/tree/master/10_virtualmemory)
	- s-matyukevitch, lesson 06
- Implement `sprintf`
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
