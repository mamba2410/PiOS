#include <mmio/mailbox.h>
#include <mmio/mmio.h>

volatile uint32_t __attribute__((aligned(16))) mailbox[36];

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

/*
 * Call the mailbox on a given channel
 * Returns 0 on success, 1 on failure
 */
uint8_t mailbox_call(uint8_t c){
	uint32_t r = ( (uint64_t)(&mailbox)&(~0xF) ) | (c&0xF);

	while( mmio_get32(MBOX_STATUS) & MBOX_FULL );
	mmio_put32(MBOX_WRITE, r);

	while(1){
		while( mmio_get32(MBOX_STATUS) & MBOX_EMPTY );
		if( r == mmio_get32(MBOX_READ) ) return mailbox[1] != MBOX_RESPONSE;
	}

	return 1;
}
