# TODO

## Bugfixes

## Features
- Interrupts
	- Put interrupt polling in a loop, multiple interrupts could come at once
	- Give unhandled interrupts better messages
- Implement `sprintf`
- Rewrite mailbox code to be better
- Random numbers
	- Pseudo-random
	- Hardware backed?	
- `delay_millis()` `delay_micros()` functions
	- Might want system clock freq as global constan/variable
	- When `delay` is called, also schedule and switch tasks for a given time
- Power managment
	- Shutdown the pi
	- Reboot the pi
	- Maybe get an echo loop, if input `r` and `h` in serial, reset and halt

## Optimisation
- Change `mmio_get32()` and `mmio_put32()` to be more efficient.
- Change mailboxes to use bit fields
	- Mailboxes should just be better implemented in general

## Research
- Mailboxes, how they work, how to interact etc
- Different scheduler types
	- Round robin
	- Most needed etc
- Filesystems
	- FAT32
	- ext4
