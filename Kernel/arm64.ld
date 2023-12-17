ENTRY(_Reset)
SECTIONS
{
	/* FIXME: make relocatable */
	. = 0x40000000;
	.startup . : { Arc.elf.p/Startup.o(.text) }
	.text : { *(.text) }
	.data : { *(.data) }
	.bss : { *(.bss COMMON) }
	. = ALIGN(8);
	. = . + 0x1000; /* 4kB of stack memory */
	stack_top = .;
	. = . + 0x200000; /* 2MB of heap memory */
	. = ALIGN(1024);
	heap_top = .;
}
