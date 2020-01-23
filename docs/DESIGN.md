# pios Design Document

## What should this do?

- Print serial
	- mini uart
	- PL011 uart
- Manage memory
	- Virtual memory
	- Heap
	- Paging
- Communicate with peripherals
	- MMIO (required for serial)
- Multi-core (for now)
- Processes
	- Process scheduling
	- User level
	- Kernel level
	- Process forking etc
- Filesystems
	- FAT32
	- ext4
- Output on HDMI
	- Character rendering
	- Put printf on screen and not serial
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
- Custom WM, DE
