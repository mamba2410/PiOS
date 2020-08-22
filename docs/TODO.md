# TODO

## Bugfixes
None that I'm aware of.
There are likely loads with virtual memory.


## Frontburner
- Map local timer register memory.
	- Register starts at `0x40000000` (1GB) which is also the high memory limit.
	- Do more research on the actual memory maps.
- Separate user code better
- User level printf access.
- User level scheduling.
- [btzsrc virtual memory](https://github.com/bztsrc/raspi3-tutorial/tree/master/10_virtualmemory)
- Clean up code a little bit. `mem` depends on `tasks` and `tasks` depends on `mem`.


## Exercises
- 04/2 - Allow task max lifetimes to change on init.
- 04/4 - Allow unlimited number of tasks.
- 06/1 - [QEMU virtual memory](https://github.com/s-matyukevich/raspberry-pi-os/blob/master/docs/lesson06/exercises.md)


## Tests
- Print memory map when tasks switch etc. Make sure sp etc are in the right place.


## Features/Research
- User processes
	- `fork` `kfork` `clone` `kclone` etc
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
- Different scheduler types
	- Round robin
	- Completely Fair Scheduler (CFS)
	- Most needed etc
- Filesystems
	- [FAT32](https://github.com/bztsrc/raspi3-tutorial/tree/master/0C_directory)
	- ext4


