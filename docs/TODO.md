# TODO

- Add full UART port
	- User can change between uart and mini uart
	- Change printf to call a macro function instead of `mini_uart_putc`
- Implement `sprintf`
- Implement a baud rate, calculated by `baudrate = system_clock_freq / (8*(baudrate_register+1))` and `system_clock_freq=250MHz`

