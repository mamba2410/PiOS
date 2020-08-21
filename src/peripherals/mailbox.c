#include <addresses/mailbox.h>
#include <memory/mem.h>
#include <peripherals/mailbox.h>
#include <peripherals/mmio.h>

static volatile uint32_t __attribute__((aligned(16))) mailbox[MBOX_MAX_SIZE];



/*
 * Call the mailbox on a given channel
 * Returns 0 on success, 1 on failure
 */
uint8_t mailbox_call(uint8_t c){
	uint32_t r = ( (uint64_t)(&mailbox)&(~0xF) ) | (c&0xF);

	while( mmio_get32(MBOX_REG_STATUS) & MBOX_STATUS_FULL );
	mmio_put32(MBOX_REG_WRITE, r);

	while(1){
		while( mmio_get32(MBOX_REG_STATUS) & MBOX_STATUS_EMPTY );
		if( r == mmio_get32(MBOX_REG_READ) ) return mailbox[1] != MBOX_RESPONSE;
	}

	return 1;
}

/*
 *	Given mailbox_t object, convert it into raw bytes and send it to the channel
 *	total size, request and last tag are automatically set
 */
uint8_t mailbox_send(mailbox_t *mbox, uint8_t channel) {
	uint32_t sz;

	// Size of the tag value buffer, 4-byte aligned
	sz = mbox->value_size + 4;					// Increase value buffer size for tag_rr
	if( sz&0x3 ) sz = (sz&(~0x3)) + 0x3;		// Align size to next 4 bytes
	mbox->value_size = sz;						// Set the size
	mbox->value_u32[ sz>>2 ] = MBOX_TAG_LAST;	// Set the next entry to be the last tag

	// Size of the whole mailbox, 16-byte aligned
	sz = mbox->value_size + MBOX_HEADER_SIZE + MBOX_TAG_HEADER_SIZE + MBOX_FOOTER_SIZE;
	if( sz&0xF ) sz = (sz&(~0xF)) + 0xF;		// Align to next 16 bytes
	mbox->buffer_size = sz;						// Set total size
	
	mbox->rr = MBOX_REQUEST;					// Assume this is a request, we aren't responding to the GPU

	memcpy((uint64_t)&mailbox, (uint64_t)mbox, mbox->buffer_size);		// Copy the memory over
	return mailbox_call(channel);										// Do the actual call
}


/*
 *	Copy the mailbox into a given pointer
 */
uint8_t mailbox_get(mailbox_t *mbox) {
	memcpy((uint64_t)mbox, (uint64_t)&mailbox, mailbox[0]);
	return 0;
}

