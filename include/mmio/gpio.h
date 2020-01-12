#ifndef GPIO_H
#define GPIO_H

#include <mmio/mmio.h>

#define GPIO_BASE		(MMIO_BASE+0x00200000)

#define GPFSEL0         (GPIO_BASE+0x00)
#define GPFSEL1         (GPIO_BASE+0x04)
#define GPFSEL2         (GPIO_BASE+0x08)
#define GPFSEL3         (GPIO_BASE+0x0C)
#define GPFSEL4         (GPIO_BASE+0x10)
#define GPFSEL5         (GPIO_BASE+0x14)
#define GPSET0          (GPIO_BASE+0x1C)
#define GPSET1          (GPIO_BASE+0x20)
#define GPCLR0          (GPIO_BASE+0x28)
#define GPLEV0          (GPIO_BASE+0x34)
#define GPLEV1          (GPIO_BASE+0x38)
#define GPEDS0          (GPIO_BASE+0x40)
#define GPEDS1          (GPIO_BASE+0x44)
#define GPHEN0          (GPIO_BASE+0x64)
#define GPHEN1          (GPIO_BASE+0x68)
#define GPPUD           (GPIO_BASE+0x94)
#define GPPUDCLK0       (GPIO_BASE+0x98)
#define GPPUDCLK1       (GPIO_BASE+0x9C)

#define SYS_CLOCK_FREQ		250e6									// System clock frequency is 250MHz
#define BAUD_RATE			115200									// Chosen baud rate
#define BAUD_RATE_REG_VAL	(SYS_CLOCK_FREQ/(8 * BAUD_RATE) - 1)	// Calculate the register value for the baud rate

#endif
