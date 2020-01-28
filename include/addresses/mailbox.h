#ifndef ADDR_MAILBOX_H
#define ADDR_MAILBOX_H


#include <addresses/addr_base.h>

#define MBOX_REG_BASE		(MMIO_BASE+0x0000B880)

#define MBOX_REG_READ       (MBOX_REG_BASE+0x00)
#define MBOX_REG_POLL       (MBOX_REG_BASE+0x10)
#define MBOX_REG_SENDER     (MBOX_REG_BASE+0x14)
#define MBOX_REG_STATUS     (MBOX_REG_BASE+0x18)
#define MBOX_REG_CONFIG     (MBOX_REG_BASE+0x1C)
#define MBOX_REG_WRITE      (MBOX_REG_BASE+0x20)


#endif /* ADDR_MAILBOX_H */
