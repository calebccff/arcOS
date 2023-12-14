
#include <Arc/stdint.h>
#include <Arc/memory.h>
#include <Arc/printk.h>
#include <Drivers/Core.h>

#include "private.h"

extern "C" {
void init(addr_t sp_base) {
	/* 256Mb or something... */
	malloc_init(ALIGN(sp_base, 0x1000), 0x40000000);
	//driver_init();

	puts("Hello, world!\n");
	log_error("This is a test error message");
	log_info("Test '%s', 0x%x, %d, %c", "string", 0xdeadbeef, 123, 'c');
}
}
