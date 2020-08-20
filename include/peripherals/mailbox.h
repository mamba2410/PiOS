#ifndef MAILBOX_H
#define MAILBOX_H

// Channels (4-bit)
#define MBOX_CH_POWER		0x0
#define MBOX_CH_FB			0x1
#define MBOX_CH_VUART		0x2
#define MBOX_CH_VCHIQ		0x3
#define MBOX_CH_LEDS		0x4
#define MBOX_CH_BTNS		0x5
#define MBOX_CH_TOUCH		0x6
#define MBOX_CH_COUNT		0x7
#define MBOX_CH_PROP		0x8

// Tags (32-bit)
#define MBOX_TAG_GETMODEL	0x00010001		// Get the board model
#define MBOX_TAG_GETREV		0x00010002		// Get the board revision
#define MBOX_TAG_GETMAC		0x00010003		// Get MAC address 
#define MBOX_TAG_GETSERIAL	0x00010004		// Get serial number
#define MBOX_TAG_GETCLKS	0x00030001		// Get clock state
#define MBOX_TAG_SETCLKS	0x00038001		// Set clock state
#define MBOX_TAG_GETCLKR	0x00030002		// Get clock rate
#define MBOX_TAG_SETCLKR	0x00038002		// Set clock rate
#define MBOX_TAG_LAST		0x00000000		// Last byte in array

// Magic numbers
#define MBOX_REQUEST		0x00000000		// rr code for a request
#define MBOX_RESPONSE		0x80000000		// rr code for request successful
#define MBOX_RESPONSE_ERR	0x80000001		// rr code for request error
#define MBOX_FULL			0x80000000
#define MBOX_EMPTY			0x40000000
#define MBOX_TAG_REQUEST	(0<<31)
#define MBOX_TAG_RESPONSE	(1<<31)

#define MAILBOX_MAX_PAYLOAD_U32		8			// Max number of u32 entries for the tag value buffer
#define MAILBOX_MAX_PAYLOAD_BYTES	(4*MAILBOX_MAX_PAYLOAD_U32)	
#define MAILBOX_HEADER_SIZE			(2*4)		// Header is 2*u32 = 8 bytes
#define MAILBOX_TAG_HEADER_SIZE		(3*4)		// Tag header is 3*u32 = 12 bytes
#define MAILBOX_FOOTER_SIZE			(1*4)		// Last tag is 1*u32 = 4 bytes

#define MAILBOX_MAX_SIZE			(MAILBOX_HEADER_SIZE + MAILBOX_TAG_HEADER_SIZE\
									+ MAILBOX_MAX_PAYLOAD_BYTES + MAILBOX_FOOTER_SIZE)


/*
 * C things
 */
#ifndef __ASSEMBLER__
#include <stdint.h>



/*
 *	Mailbox struct
 *	Each mailbox can accept multiple tags at once, but
 *	since tags are variable in length, this is hard to
 *	do in a struct, so only one (technically two) tags
 *	are sent at once.
 *	For more info see https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
 */
typedef struct {
	uint32_t	buffer_size;		// Total size of buffer
	uint32_t	rr;					// Budder request/response code
	uint32_t	tag_id;				// Tag ID, start of tag 1
	uint32_t	value_size;			// Tag payload size
	uint32_t	tag_rr;				// Tag request/response code
	union {							// Tag value buffer as bytes or u32
		uint8_t		value_bytes[MAILBOX_MAX_PAYLOAD_BYTES];
		uint32_t	value_u32[MAILBOX_MAX_PAYLOAD_U32];
	};
	uint32_t	tag_last;			// Last tag, in case the value buffer is full
} mailbox_t;

/*
 *	Tag structure for the mailbox
 *	Value buffer can vary in size and must be padded to be u32-aligned
 */
/*
typedef struct {
	uint32_t	id;		// ID
	uint32_t	size;	// Value buffer size in bytes
	uint32_t	rr;		// Request/response code
	union {				// Value buffer as u32 or bytes
		uint8_t		value_bytes[MAILBOX_MAX_PAYLOAD_BYTES];
		uint32_t	value_u32[MAILBOX_MAX_PAYLOAD_U32];
	};
} mailbox_tag_t;
*/

uint8_t mailbox_call(uint8_t);
uint8_t	mailbox_send(mailbox_t *mbox, uint8_t channel);
uint8_t	mailbox_get(mailbox_t *dst);

#endif /* __ASSEMBLER__ */

#endif /* MAILBOX_H */
