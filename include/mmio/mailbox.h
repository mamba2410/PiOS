#ifndef MAILBOX_H
#define MAILBOX_H

// Channels
#define MBOX_CH_POWER		0
#define MBOX_CH_FB			1
#define MBOX_CH_VUART		2
#define MBOX_CH_VCHIQ		3
#define MBOX_CH_LEDS		4
#define MBOX_CH_BTNS		5
#define MBOX_CH_TOUCH		6
#define MBOX_CH_COUNT		7
#define MBOX_CH_PROP		8

// Tags
#define MBOX_TAG_GETSERIAL	0x10004
#define MBOX_TAG_SETCLK		0x38002
#define MBOX_TAG_LAST		0x00000

// Magic numbers
#define MBOX_REQUEST		0x00000000
#define MBOX_RESPONSE		0x80000000
#define MBOX_FULL			0x80000000
#define MBOX_EMPTY			0x40000000


/*
 * C things
 */
#ifndef __ASSEMBLER__
#include <stdint.h>

extern volatile uint32_t mailbox[36];
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

#endif /* __ASSEMBLER__ */

#endif /* MAILBOX_H */
