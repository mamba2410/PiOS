# pios

Barebones operating system for the raspberry pi

## Resources
[osdev wiki](https://wiki.osdev.org/ARM_RaspberryPi_Tutorial_C)
[btzsrc github](https://github.com/bztsrc/raspi3-tutorial)
[s-matyukevich github](https://github.com/s-matyukevich/raspberry-pi-os)

## Testing
Test this with either qemu or actual hardware.

### QEMU
For the `pi3` branch, use

```
qemu-system-aarch64 -M raspi3 -kernel bin/kernel8.img -curses -serial null -serial stdio
```

For a system that emulates a pi 3 with the 64-bit kernel, has no window (runs in terminal mode) and redirects uart0 to null and usrt1 (mini uart) to stdio.
Don't yet know how to exit qemu from here, I just `killall qemu-system-aarch64`

### Hardware
Connect up a USB-to-TTL cable to the pc and raspi.
Make sure to connect GND (black), TXD (white) and RXD (green) and NOT power (red).

On the pi 3B the pins should all be next to each other, 3 in a row.

Connect both ends of the USB-to-TTl cable whilst the pi is off.
Run
```
sudo screen /dev/ttyUSB0 115200
```
or exchange it for the serial port and baud rate as needed.

Once screen is up, power on the pi and go for it, you should see serial output.

Tip: exit `screen` with `C-a + d`. Will need to kill screen afterwards though, have a look to see if theres a key that does that already.

