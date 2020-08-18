#ifndef _ADDR_BASE_H
#define _ADDR_BASE_H

#include <addresses/vmem.h>

#define MMIO_BASE_PHYS		0x3F000000
#define LOCAL_BASE_PHYS		0x40000000		// Apparently this is a thing
											// see https://github.com/s-matyukevich/raspberry-pi-os/issues/70
#define MMIO_BASE			(VA_START + MMIO_BASE_PHYS)
#define LOCAL_BASE			(VA_START + LOCAL_BASE_PHYS)

#endif /* _ADDR_BASE_H */
