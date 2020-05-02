#ifndef ARM_SYSTEM_REGISTERS_H
#define ARM_SYSTEM_REGISTERS_H

/*
 * Define the exception levels
 */
#define Current_EL_EL1				(1<<2)
#define Current_EL_EL2				(2<<2)
#define Current_EL_EL3				(3<<2)
#define Current_EL_EL4				(4<<2)


/*
 * SCTLR_EL1, System Control Register (EL1), AArch64-Reference-Manual page 2654
 */
#define SCTLR_RESERVED              (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)
#define SCTLR_EE_LITTLE_ENDIAN      (0 << 25)
#define SCTLR_EOE_LITTLE_ENDIAN     (0 << 24)
#define SCTLR_I_CACHE_DISABLED      (0 << 12)
#define SCTLR_D_CACHE_DISABLED      (0 << 2)
#define SCTLR_MMU_DISABLED          (0 << 0)
#define SCTLR_MMU_ENABLED           (1 << 0)

#define SCTLR_VALUE_MMU_DISABLED	(SCTLR_RESERVED | SCTLR_EE_LITTLE_ENDIAN | SCTLR_I_CACHE_DISABLED | SCTLR_D_CACHE_DISABLED | SCTLR_MMU_DISABLED)

/*
 * HCR_EL2, Hypervisor Configuration Register (EL2), page 2487
 */
#define HCR_RW	    				(1 << 31)
#define HCR_VALUE					HCR_RW

/*
 * SCR_EL3, Secure Configuration Register (EL3), page 2648
 */
#define SCR_RESERVED	    		(3 << 4)
#define SCR_RW						(1 << 10)
#define SCR_NS						(1 << 0)
#define SCR_VALUE	    	    	(SCR_RESERVED | SCR_RW | SCR_NS)

/*
 * SPSR_EL3, Saved Program Status Register (EL3), page 389
 */
#define SPSR_MASK_ALL 				(7 << 6)
#define SPSR_EL0t					(0 << 0)
#define SPSR_EL1t					(4 << 0)
#define SPSR_EL1h					(5 << 0)
#define SPSR_EL2t					(8 << 0)
#define SPSR_EL2h					(9 << 0)
#define SPSR_EL3_VALUE				(SPSR_MASK_ALL | SPSR_EL2h)
#define SPSR_EL2_VALUE				(SPSR_MASK_ALL | SPSR_EL1h)

/*
 * ESR_EL1, Exception Syndrome Register (EL1)
 */
#define ESR_ELx_EC_SHIFT			26
#define ESR_ELx_EC_SVC64			0x15

#endif // ARM_SYSTEM_REGISTERS_H
