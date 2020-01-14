#ifndef ADDR_IRQ_H
#define ADDR_IRQ_H

#include <addresses/mmio_base.h>

#define IRQ_BASIC_PENDING	((uint64_t*)(MMIO_BASE+0x0000B200))
#define IRQ_PENDING_1		((uint64_t*)(MMIO_BASE+0x0000B204))
#define IRQ_PENDING_2		((uint64_t*)(MMIO_BASE+0x0000B208))
#define FIQ_CONTROL			((uint64_t*)(MMIO_BASE+0x0000B20C))
#define ENABLE_IRQS_1		((uint64_t*)(MMIO_BASE+0x0000B210))
#define ENABLE_IRQS_2		((uint64_t*)(MMIO_BASE+0x0000B214))
#define ENABLE_BASIC_IRQS	((uint64_t*)(MMIO_BASE+0x0000B218))
#define DISABLE_IRQS_1		((uint64_t*)(MMIO_BASE+0x0000B21C))
#define DISABLE_IRQS_2		((uint64_t*)(MMIO_BASE+0x0000B220))
#define DISABLE_BASIC_IRQS	((uint64_t*)(MMIO_BASE+0x0000B224))

#endif /* ADDR_IRQ_H */
