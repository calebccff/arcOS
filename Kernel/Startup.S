#include <asm/macro.h>

#.global Vectors
.global _Reset
_Reset:
    ldr x30, =stack_top	// setup stack
    mov sp, x30
#    ldr x1, =Vectors // setup vector table
    msr vbar_el1, x1
    mov x0, x30
    bl init
    b .
