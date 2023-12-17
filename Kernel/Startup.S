#include <asm/macro.h>

/* System Control Register (EL1) */
.equ	SCTLR_EL1_AARCH32_RES1_MSB,	1 << 23 | 1 << 22
.equ	SCTLR_EL1_AARCH32_RES1_LSB,	1 << 11 | 1 << 4 | 1 << 3
.equ	SCTLR_EL1_CP15BEN,		1 << 5	/* enable CP15 barrier */

/* SMC Calling Convention bits */
.equ	SMCCC_OEN_SHIFT,		24
.equ	SMCCC_OEN_MASK,			0x3f
.equ	SMCCC_OEN_SIP,			2
.equ	SMCCC_OEN_FUNC_MASK,		0xffff

/* SMC Calling Convention return codes */
.equ	SMCCC_NOT_SUPPORTED,		-1
.equ	SMCCC_INVALID_PARAMETER,	-3

#.global Vectors
.global _Reset
_Reset:
    ldr x0, =el2_vector_table // setup vector table
    msr vbar_el2, x0
    ldr x30, =stack_top	// setup stack
    mov sp, x30
    // Pass heap address to kernel
    ldr x0, =heap_top // setup heap
    bl init
    b .

panic:
	b	panic

/* We don't support HVC calls yet... */
eret_not_supported:
	mov	w0, SMCCC_NOT_SUPPORTED
	eret

/* EL2 exception vectors (written to VBAR_EL2) */
.section .text.vectab
.macro excvec label
	/* Each exception vector is 32 instructions long, so 32*4 = 2^7 bytes */
	.align 7
\label:
.endm

.align	11	/* Exception vector table must be aligned to 0x800 */
el2_vector_table:
	excvec	el2_sp0_sync
	b	panic
	excvec	el2_sp0_irq
	b	panic
	excvec	el2_sp0_fiq
	b	panic
	excvec	el2_sp0_serror
	b	panic

	excvec	el2_sp2_sync
	b	panic
	excvec	el2_sp2_irq
	b	panic
	excvec	el2_sp2_fiq
	b	panic
	excvec	el2_sp2_serror
	b	panic

	excvec	el1_aarch64_sync
	b	panic
	excvec	el1_aarch64_irq
	b	panic
	excvec	el1_aarch64_fiq
	b	panic
	excvec	el1_aarch64_serror
	b	panic

	excvec	el1_aarch32_sync
	b	eret_not_supported
	b	panic
	excvec	el1_aarch32_irq
	b	panic
	excvec	el1_aarch32_fiq
	b	panic
	excvec	el1_aarch32_serror
	b	panic

	excvec	el2_vector_table_end
