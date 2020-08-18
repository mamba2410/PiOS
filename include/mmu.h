#ifndef _MMU_H
#define _MMU_H

#define MM_TYPE_PAGE_TABLE		0b11
#define MM_TYPE_PAGE			0b11
#define MM_TYPE_BLOCK			0b01
#define MM_ACCESS				(1<<10)
#define MM_ACCESS_PERMISSION	(0x01<<6)

/*
 *	Memory region attributes to set in the mair
 *	n => 0x0 - 0x7	(8 values)
 *
 *	Region type			n		MAIR bits
 *	DEVICE_nGnRnE		0x0		00000000
 *	NORMAL_NC			0x1		01000100
 *
 *	MAIR_EL1, Memory Attribute Indirection Register (EL1), AArch64 Reference Manual page 3338
 */
#define MT_DEVICE_nGnRnE		0x0			// Device registers
#define MT_DEVICE_nGnRnE_FLAGS	0x00
#define MT_NORMAL_NC			0x1			// Normal, non-cacheable memory
#define MT_NORMAL_NC_FLAGS		0x44

#define MAIR_VALUE				(MT_DEVICE_nGnRnE_FLAGS<<(8*MT_DEVICE_nGnRnE)|MT_NORMAL_NC_FLAGS<<(8*(MT_NORMAL_NC)))

#define MMU_NNC_FLAGS			(MM_TYPE_BLOCK|(MT_NORMAL_NC<<2)|MM_ACCESS)
#define MMU_DEVICE_FLAGS		(MM_TYPE_BLOCK|(MT_DEVICE_nGnRnE<<2)|MM_ACCESS)
#define MMU_PTE_FLAGS			(MM_TYPE_PAGE |(MT_NORMAL_NC<<2)|MM_ACCESS|MM_ACCESS_PERMISSION)

/*
 *	TCR_EL1, Translation Control Register (EL1), AArch64 Reference Manual page 3453
 */
#define TCR_T0SZ				(64-48)
#define TCR_T1SZ				((64-48)<<16)
#define TCR_TG0_4K				(0<<14)
#define TCR_TG1_4K				(2<<30)
#define TCR_VALUE				(TCR_T0SZ|TCR_T1SZ|TCR_TG0_4K|TCR_TG1_4K)


#endif /* _MMU_H */
