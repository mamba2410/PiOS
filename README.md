# pios

Barebones operating system for the raspberry pi.

Built using aarch64 cross compiler.

For now, just using pi3, but have plans to port it to pi1 or pi0 etc.
The hard work should already be done once the pi3 works.

## Resources
[osdev wiki](https://wiki.osdev.org/ARM_RaspberryPi_Tutorial_C)
[btzsrc github](https://github.com/bztsrc/raspi3-tutorial)
[s-matyukevich github](https://github.com/s-matyukevich/raspberry-pi-os)
[jsandler](https://jsandler18.github.io/)
[dwelch](https://github.com/dwelch67/raspberrypi)

[BCM2837 ARM Peripherals Manual](https://github.com/raspberrypi/documentation/files/1888662/BCM2837-ARM-Peripherals.-.Revised.-.V2-1.pdf)
[ARMv8-A Instruction Set Architecture](https://developer.arm.com/architectures/learn-the-architecture/armv8-a-instruction-set-architecture)
[ARM Cortex-A Programmers Guide](https://developer.arm.com/docs/den0024/latest)
[NEON Architecture](https://developer.arm.com/architectures/instruction-sets/simd-isas/neon)

[Information on linker scripts](https://sourceware.org/binutils/docs/ld/Scripts.html#Scripts)

## Testing
Test this with either qemu or actual hardware.

### QEMU
For the `pi3` branch, use

```
qemu-system-aarch64 -M raspi3 -kernel bin/kernel8.img -display none -serial null -serial stdio
```

For a system that emulates a pi 3 with the 64-bit kernel, has no window (uses stdio) and redirects uart0 to null and uart1 (mini uart) to stdio.

### Hardware
Connect up a USB-to-TTL cable to the pc and raspi.
Make sure to connect GND (black), TXD (white) and RXD (green) and NOT power (red).

On the pi 3B the pins should all be next to each other, 3 in a row.

Connect both ends of the USB-to-TTl cable whilst the pi is off.
```
sudo screen /dev/ttyUSB0 115200
```
or exchange it for the serial port and baud rate as needed.
Once screen is up, power on the pi and go for it, you should see serial output.

Tip: exit `screen` with `C-a + z`.

