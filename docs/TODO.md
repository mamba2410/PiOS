# TODO

## Bugfixes
- Fix UART0
	- Baud rate is fine
	- Registers are being set fine
	- Code example from github doesn't work, maybe it's hardware? (unlikely)
	- Is it being initialised okay?

## Features
- Interrupts
	- Put interrupt polling in a loop, multiple interrupts could come at once
	- Give unhandled interrupts better messages
- Implement `sprintf`

## Optimisation
- Change `mmio_get32()` and `mmio_put32()` to be more efficient.
- Change mailboxes to use bit fields

## Research

