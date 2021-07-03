# pios

Barebones operating system for the raspberry pi.

For now, just using pi3, but have plans to port it to other architectures.
The pi0 to pi2 will be more difficult since they are 32-bit so all of the assembly will need to be completely rewriten.

## Resources
- [osdev wiki](https://wiki.osdev.org/ARM_RaspberryPi_Tutorial_C)
- [btzsrc/raspi3-tutorial](https://github.com/bztsrc/raspi3-tutorial)
- [s-matyukevich/raspberry-pi-os](https://github.com/s-matyukevich/raspberry-pi-os)
- [jsandler github](https://jsandler18.github.io/)
- [dwelch67/raspberrypi](https://github.com/dwelch67/raspberrypi)
- [AArch64 Reference Manual](https://developer.arm.com/documentation/ddi0487/latest)
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
$ ./qemu [mi]
```
No option is PL011 UART, `m` option uses mini-uart, `i` option opens qemu info console.
There will be no display, there are currently no plans to add video display to this kernel. 
It would be a long ways off.

There is no hard drive for this, as well as next to no peripherals.
The system timer interrupts do not work for instance.

### Hardware
Connect up a USB-to-TTL cable to the pc and raspi.
Make sure to connect GND (black), TXD (white) and RXD (green) and NOT power (red).

```
   3v3 ---> x x <--- 5V
GPIO 2 ---> x x <--- 5V
GPIO 3 ---> x x <--- GND (black wire)
GPIO 4 ---> x x <--- TXD (white wire)
   GND ---> x x <--- RXD (green wire)
~~~~~~~~~~~ === ~~~~~~~~~~~~
```

Connect both ends of the USB-to-TTl cable whilst the pi is off.
```
$ screen /dev/ttyUSB0 115200
```
Exchange it for the serial port and baud rate as needed.
Once screen is up, power on the pi and go for it, you should see serial output.

Screen tips:
- Make sure the user is in the `dialout` group, you may need to restart to take effect.
- Exit `screen` with `C-a + \ + y`
- Clear output with `C-a + Shift-C`
- Send ascii files with
```
$ screen -S $session_name -x readreg p /path/to/file
$ screen -S $session_name -x paste p
```

