# pios Design Document

I know nothing really about operating systems or anything so this is just gonna be my best attempt at copying the linux functionality.
I don't really want to make this too complicated, that's not the point.
This is mainly just an exercise in low-level programming and interacting with the hardware and embedded systems etc.

It's hard to write a design document for something you don't even know what you're doing.

## What should this do?

- Print serial
	- mini uart
	- PL011 uart
- Manage memory
	- Virtual memory
	- Heap
	- Paging
- Communicate with peripherals
	- PL011 UART
	- Mini uart
	- MMIO (required for serial)
	- Interrupt controllers, like timers
- Multi-core
- Processes
	- Process scheduling
	- User level
	- Kernel level
	- Process forking etc
- Filesystems
	- FAT32
	- ext4
- Interaction
	- Users can run their own code by putting it on the SD card
	- Separate coreutils, like gnu coreutils. Make another repo for this
	- Interaction over serial
- Output streams
	- stdio
	- serial
	- files


## What should I integrate this with?
- Custom shell, see [lsh]()
	- `cd`, `exit`, internal things
	- Process forking
	- Program launching
	- Output pipes
	- Scripts / language
- Custom filesystem?
