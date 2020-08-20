#include <addresses/mailbox.h>
#include <memory/mem.h>
#include <peripherals/mailbox.h>
#include <peripherals/mmio.h>

static volatile uint32_t __attribute__((aligned(16))) mailbox[MAILBOX_MAX_SIZE];

/*
 * Mailboxes are messages sent to the GPU from the CPU, done via MMIO
 * Mailbox should be a 16-byte aligned buffer of 4 byte (32-bit) words
 *
 * Mailbox message looks like the following
 * 0x00		Buffer size
 * 0x04		Request/response code
 * 0x08		Tags
 * ...
 * 0xXX+4	End tag (0)
 * 0xXX+8	Padding
 * 0xXX+16	Padding
 *
 * Tags look like
 * 0x00		Tag ID
 * 0x04		Value buffer size (bytes)
 * 0x08		Request/response code
 * 0x0C		Value buffer (uint8_t array, not uint32_t like the rest)
 * 0xXX		Value buffer/padding
 * Tags need to be 4-byte aligned, but since value buffers are uint8_t arrays, 
 * they may need padding to get them to 4 byte alignment
 */

uint64_t get_mbox_addr() {return (uint64_t)&mailbox;}

/*
 * Call the mailbox on a given channel
 * Returns 0 on success, 1 on failure
 */
uint8_t mailbox_call(uint8_t c){
	uint32_t r = ( (uint64_t)(&mailbox)&(~0xF) ) | (c&0xF);

	while( mmio_get32(MBOX_REG_STATUS) & MBOX_FULL );
	mmio_put32(MBOX_REG_WRITE, r);

	while(1){
		while( mmio_get32(MBOX_REG_STATUS) & MBOX_EMPTY );
		if( r == mmio_get32(MBOX_REG_READ) ) return mailbox[1] != MBOX_RESPONSE;
	}

	return 1;
}

/*
 *	Given mailbox_t object, convert it into raw bytes and send it to the channel
 *	total size, request and last tag are automatically set
 */
uint8_t mailbox_send(mailbox_t *mbox, uint8_t channel) {
	mbox->buffer_size = mbox->value_size + MAILBOX_HEADER_SIZE + MAILBOX_TAG_HEADER_SIZE + MAILBOX_FOOTER_SIZE;
	uint32_t tmp = mbox->buffer_size % 16;
	if(tmp) mbox->buffer_size += 16-tmp;
	mbox->rr = MBOX_REQUEST;												// This is a request
	mbox->value_bytes[mbox->value_size+0] = (MBOX_TAG_LAST>>12)&0xFF;		// Set the last tag to the 
	mbox->value_bytes[mbox->value_size+1] = (MBOX_TAG_LAST>>8)&0xFF;		// right value. End of buffer
	mbox->value_bytes[mbox->value_size+2] = (MBOX_TAG_LAST>>4)&0xFF;		// may not be 4-byte aligned so
	mbox->value_bytes[mbox->value_size+3] = (MBOX_TAG_LAST>>0)&0xFF;		// that's why I have to do this
	mbox->tag_last = MBOX_TAG_LAST;											// Set the last tag just in case
	memcpy((uint64_t)&mailbox, (uint64_t)mbox, mbox->buffer_size);			// Copy the memory over
	return mailbox_call(channel);											// Do the actual call
}

uint8_t mailbox_get(mailbox_t *mbox) {
	memcpy((uint64_t)mbox, (uint64_t)&mailbox, mailbox[0]);
	return 0;
}

