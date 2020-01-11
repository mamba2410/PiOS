#ifndef GPIO_H
#define GPIO_H

#define PERIPHERAL_BASE 0x3F000000

#define GPIO_BASE		0x3F200000
#define GPFSEL1         (PERIPHERAL_BASE+0x00200004)
#define GPSET0          (PERIPHERAL_BASE+0x0020001C)
#define GPCLR0          (PERIPHERAL_BASE+0x00200028)
// General putpose pull up/down register for GPIO pins
// Sets if pin should pull up, down, both or neither
#define GPPUD           (PERIPHERAL_BASE+0x00200094)
// General purpose pull up/down clock register
// Bits which are written to as 1 will have their bits set by the GPPUD register
// If written a 0, no change occurs to that pin
#define GPPUDCLK0       (PERIPHERAL_BASE+0x00200098)

#endif
