#pragma once

#ifdef ASSEMBLY

/*
 * Branch according to exception level
 */
.macro switch_el, xreg, el3_label, el2_label, el1_label
	mrs	\xreg, CurrentEL
	cmp	\xreg, #0x8
	b.gt	\el3_label
	b.eq	\el2_label
	b.lt	\el1_label
.endm

#endif
