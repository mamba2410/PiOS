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

/*
 *	Tags for the mailbox
 *	See https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
 *	for details on each tag
 */
#define MBOX_TAG_GETMODEL	0x00010001		// Get the board model
#define MBOX_TAG_GETREV		0x00010002		// Get the board revision
#define MBOX_TAG_GETMAC		0x00010003		// Get MAC address 
#define MBOX_TAG_GETSERIAL	0x00010004		// Get serial number
#define MBOX_TAG_GETCLKS	0x00030001		// Get clock state
#define MBOX_TAG_SETCLKS	0x00038001		// Set clock state
#define MBOX_TAG_GETCLKR	0x00030002		// Get clock rate
#define MBOX_TAG_SETCLKR	0x00038002		// Set clock rate
#define MBOX_TAG_GETPWR		0x00020001		// Get power state of device
#define MBOX_TAG_SETPWR		0x00028001		// Set power state of device
#define MBOX_TAG_GETTEMP	0x00030006		// Get temperature of SoC
#define MBOX_TAG_LAST		0x00000000		// Last byte in array

// Magic numbers
#define MBOX_REQUEST		0x00000000		// rr code for a request
#define MBOX_RESPONSE		0x80000000		// rr code for request successful
#define MBOX_RESPONSE_ERR	0x80000001		// rr code for request error
#define MBOX_STATUS_FULL	(1<<31)			
#define MBOX_STATUS_EMPTY	(1<<30)
#define MBOX_TAG_REQUEST	(0<<31)
#define MBOX_TAG_RESPONSE	(1<<31)
#define MBOX_RR_RES_SHIFT	31
#define MBOX_RR_SIZE_MASK	(~(1<<31))

#define MBOX_MAX_VALUE_U32			8			// Max number of u32 entries for the tag value buffer
#define MBOX_MAX_VALUE_SIZE			(4*MBOX_MAX_VALUE_U32)		// Max size of the value buffer in bytes
#define MBOX_HEADER_SIZE			(2*4)		// Header is 2*u32 = 8 bytes
#define MBOX_TAG_HEADER_SIZE		(3*4)		// Tag header is 3*u32 = 12 bytes
#define MBOX_FOOTER_SIZE			(1*4)		// Last tag is 1*u32 = 4 bytes

#define MBOX_MAX_SIZE			(MBOX_HEADER_SIZE + MBOX_TAG_HEADER_SIZE\
								+ MBOX_MAX_VALUE_SIZE + MBOX_FOOTER_SIZE)		// Max size of the mailbox in bytes


/*
 * C things
 */
#ifndef __ASSEMBLER__
#include <stdint.h>



/*
 *	Mailbox should be a 16-byte aligned buffer of 4 byte (32-bit) words
 *	For more info see https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
 *	
 *	Mailbox message looks like the following
 *	0x00		Buffer size
 *	0x04		Request/response code
 *	0x08		Tags
 *	...
 *	0xXX+4	End tag (0)
 *	0xXX+8	Padding to 16-byte aligned
 *	
 *	
 *	Tags look like
 *	0x00		Tag ID
 *	0x04		Value buffer size (bytes)
 *	0x08		Tag request/response code (included in the value buffer size)
 *	0x0C		Value buffer
 *	0xXX		Padding to 4-byte aligned
 *
 */
typedef struct {
	uint32_t	buffer_size;		// Total size of buffer
	uint32_t	rr;					// Buffer request/response code
	uint32_t	tag_id;				// Tag ID, start of tag 1
	uint32_t	value_size;			// Tag payload size
	uint32_t	tag_rr;				// Tag request/response code
	union {							// Tag value buffer as bytes or u32
		uint8_t		value_bytes[MBOX_MAX_VALUE_SIZE];
		uint32_t	value_u32[MBOX_MAX_VALUE_U32];
	};
	uint32_t	tag_last;			// Reserve space for the last tag
	// Should pad it to 16-byte aligned but I don't think it will matter as
	// long as the size argument is right
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
		uint8_t		value_bytes[MBOX_MAX_PAYLOAD_BYTES];
		uint32_t	value_u32[MBOX_MAX_PAYLOAD_U32];
	};
} mailbox_tag_t;
*/

uint8_t mailbox_call(uint8_t);
uint8_t	mailbox_send(mailbox_t *mbox, uint8_t channel);
uint8_t	mailbox_get(mailbox_t *dst);

#endif /* __ASSEMBLER__ */

#endif /* MAILBOX_H */
