#ifndef MAILBOX_H
#define MAILBOX_H

#include <stdint.h>

extern volatile uint32_t mailbox[36];

#define MBOX_REQUEST	0

// Channels
#define MBOX_CH_POWER	0
#define MBOX_CH_FB		1
#define MBOX_CH_VUART	2
#define MBOX_CH_VCHIQ	3
#define MBOX_CH_LEDS	4
#define MBOX_CH_BTNS	5
#define MBOX_CH_TOUCH	6
#define MBOX_CH_COUNT	7
#define MBOX_CH_PROP	8

// Tags
#define MBOX_TAG_GETSERIAL	0x10004
#define MBOX_TAG_LAST		0


#define VIDEOCORE_MBOX  MMIO_BASE+0x0000B880
#define MBOX_READ       ((uint64_t*)(VIDEOCORE_MBOX+0x00))
#define MBOX_POLL       ((uint64_t*)(VIDEOCORE_MBOX+0x10))
#define MBOX_SENDER     ((uint64_t*)(VIDEOCORE_MBOX+0x14))
#define MBOX_STATUS     ((uint64_t*)(VIDEOCORE_MBOX+0x18))
#define MBOX_CONFIG     ((uint64_t*)(VIDEOCORE_MBOX+0x1C))
#define MBOX_WRITE      ((uint64_t*)(VIDEOCORE_MBOX+0x20))
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

// Bit field struct for a mailbox message
typedef struct{
	uint8_t channel : 4;
	uint32_t data : 28;
} mailbox_message_t;

// Bit field struct for a mailbox status
typedef struct{
	uint32_t reserved : 30;
	uint8_t empty : 1;
	uint8_t full : 1;
} mailbox_status_t;

uint8_t mailbox_call(uint8_t);

#endif /* MAILBOX_H */
