#include <testing.h>
#include <peripherals/mmio.h>
#include <misc/printf.h>
#include <misc/syscalls.h>
#include <proc/fork.h>
#include <proc/tasks.h>
#include <user_test.h>

#include <peripherals/mailbox.h>
#include <addresses/mailbox.h>

void print_bytes(uint64_t start, uint64_t size) {
	for(uint64_t i = 0; i < size; i+=2) {
		printf("%04x ", *((uint16_t*)(start+i)));
	}
	printf("\n");
}

void testing_main(){
	int32_t result;
	mailbox_t mbox;

	
	mbox.tag_id		= MBOX_TAG_GETMODEL;
	mbox.value_size	= 0;
	mbox.tag_rr		= MBOX_TAG_REQUEST;
	result = (int32_t)mailbox_send(&mbox, MBOX_CH_PROP);
	if(result>0){ printf("[E] Failed to send mailbox\n"); }
	mailbox_get(&mbox);
	printf("[T] Board model %08x (r: %d, s:%d)\n",
			mbox.value_u32[0], mbox.tag_rr>>31, mbox.tag_rr&(~(1<<31)));
	print_bytes((uint64_t)&mbox, MAILBOX_MAX_SIZE);

	printf("[D] Resp addr: %08x; mbox addr: %08x\n", mmio_get32(MBOX_REG_READ), get_mbox_addr());

	mbox.tag_id		= MBOX_TAG_GETREV;
	mbox.value_size	= 0;
	mbox.tag_rr		= MBOX_TAG_REQUEST;
	result = (int32_t)mailbox_send(&mbox, MBOX_CH_PROP);
	if(result>0){ printf("[E] Failed to send mailbox\n"); }
	mailbox_get(&mbox);
	printf("[T] Board revision %08x (r: %d, s:%d)\n",
			mbox.value_u32[0], mbox.tag_rr>>31, mbox.tag_rr&(~(1<<31)));
	print_bytes((uint64_t)&mbox, MAILBOX_MAX_SIZE);
	

	mbox.tag_id		= MBOX_TAG_GETSERIAL;
	mbox.value_size	= 0;
	mbox.tag_rr		= MBOX_TAG_REQUEST;
	result = (int32_t)mailbox_send(&mbox, MBOX_CH_PROP);
	if(result>0){ printf("[E] Failed to send mailbox (%d)\n", result); }
	mailbox_get(&mbox);
	printf("[D] mbox.rr: %08x\n", mbox.rr);
	printf("[T] Serial number: %08x%08x (r: %d, s:%d)\n",
			mbox.value_u32[0], mbox.value_u32[1], mbox.tag_rr>>31, mbox.tag_rr&(~(1<<31)));
	print_bytes((uint64_t)&mbox, MAILBOX_MAX_SIZE);
	printf("[D] Request addr?: %08x\n", *(uint64_t*)(VA_START+mbox.value_u32[0]));

	result = create_process(PF_KERNEL_THREAD, (uint64_t)(&kernel_process), 0);
	if( result < 0 ){ printf("[E] Error whilst starting kernel process\n"); return; }
}

void kernel_process(){
	uint64_t start	= (uint64_t)&__user_start;
	uint64_t end	= (uint64_t)&__user_end;
	uint64_t proc	= (uint64_t)&user_process;

	printf("[T] Kernel process started at EL%d\n", get_exception_level());
	int8_t error = move_to_user(start, end-start, proc-start);
	if(error < 0) printf("[E] Error whilst moving kernel process to user mode.\n");

	printf("[T] Kernel process done\n");
	return;
}

