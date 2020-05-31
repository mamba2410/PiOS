# pios

Barebones operating system for the raspberry pi.

For now, just using pi3, but have plans to port it to other architectures.
The pi0 to pi2 will be more difficult since they are 32-bit so all of the assembly will need to be completely rewriten.

## Resources
- [osdev wiki](https://wiki.osdev.org/ARM_RaspberryPi_Tutorial_C)
- [btzsrc/raspi3-tutorial](https://github.com/bztsrc/raspi3-tutorial)
- [s-matyukevich/raspberry-pi-os)](https://github.com/s-matyukevich/raspberry-pi-os)
- [jsandler github](https://jsandler18.github.io/)
- [dwelch67/raspberrypi)](https://github.com/dwelch67/raspberrypi)

- [BCM2837 ARM Peripherals Manual](https://github.com/raspberrypi/documentation/files/1888662/BCM2837-ARM-Peripherals.-.Revised.-.V2-1.pdf)
- [BCM2711 ARM Peripherals Manual](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2711/rpi_DATA_2711_1p0.pdf)
- [ARMv8-A Instruction Set Architecture](https://developer.arm.com/architectures/learn-the-architecture/armv8-a-instruction-set-architecture)
- [ARM Cortex-A Programmers Guide](https://developer.arm.com/docs/den0024/latest)
- [NEON Architecture](https://developer.arm.com/architectures/instruction-sets/simd-isas/neon)

- [Information on linker scripts](https://sourceware.org/binutils/docs/ld/Scripts.html#Scripts)

## Testing
Test this with either qemu or actual hardware.

### QEMU
For the `pi3` branch, use

```
$ qemu-system-aarch64 -M raspi3 -kernel bin/kernel8.img -display none -serial null -serial stdio
```
This emulates a Raspberry Pi 3 SoC with the specified kernel.
Note: There are no timer interrupts in this emulator, so timed scheduling won't work.

The first `-serial` flag is for the default `UART0` port, the second is for the auxiliary `UART1` or mini uart port.
Both cannot be on `stdio`.

There will be no display, there are currently no plans to add video display to this kernel. 
It would be a long ways off.

There is no hard drive for this, as well as next to no peripherals.
The system timer interrupts do not work for instance.

### Hardware
Connect up a USB-to-TTL cable to the pc and raspi.
Make sure to connect GND (black), TXD (white) and RXD (green) and NOT power (red).

On the pi 3B the pins should all be next to each other, 3 in a row.

Connect both ends of the USB-to-TTl cable whilst the pi is off.
```
$ screen /dev/ttyUSB0 115200
```
Exchange it for the serial port and baud rate as needed.
Once screen is up, power on the pi and go for it, you should see serial output.

Make sure the user is in the `dialout` group, you may need to restart to take effect.
You might also need to kill `screen` with
```
$ killall screen
```

Tip: exit `screen` with `C-a + \`.

