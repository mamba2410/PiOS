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
#define SCTLR_VALUE_MMU_ENABLED	(SCTLR_MMU_ENABLED)

/*
 * CPACR_EL1, Architectural Feature Access Control Register (EL1), AArch64 Reference Manual page 2938
 */
#define CPACR_TRAP_ALL				(0<<20)
#define CPACR_TRAP_EL0				(1<<20)
#define CPACR_TRAP_EL01				(1<<21)
#define CPACR_TRAP_NONE				(3<<20)
#define CPACR_VALUE					(CPACR_TRAP_NONE)

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
 * ESR_EL1, Exception Syndrome Register (EL1), page 2968 of Arm Architecture Reference Manual
 */
#define ESR_ELx_EC_SHIFT			26
#define ESR_ELx_EC_SVC64			0x15		// Supervisor call when in aarch64 state
#define ESR_ELx_EC_SVE				0x07		// Access to A-SIMD if trapped by CPACR_EL1
#define ESR_ELx_EC_MSR				0x18		// Trapped msr, mrs or system instruction execution
#define ESR_ELx_EC_DA_LOW			0x24		// Data abort to lower exception level
#define ESR_ELx_EC_DA_HIGH			0x25		// Data abort to same exception level
#define ESR_ELx_EC_SErr				0x2f		// SError interrupt
#define ESR_ELx_EC_BEL				0x30		// Breakpoint exception from lower EL
#define ESR_ELx_EC_BES				0x31		// Breakpoint exception from same EL
#define ESR_ELx_EC_UNKNOWN			0x00		// Misc exceptions. see page 2972/3 (ISS encoding) for details

#endif // ARM_SYSTEM_REGISTERS_H
