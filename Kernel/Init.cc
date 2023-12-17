
#include <Arc.h>
#include <Arc/stdint.h>
#include <Arc/memory.h>
#include <Arc/printk.h>
#include <Drivers/Core.h>

#include "private.h"

extern "C" {

void init(addr_t heap_top) {
	/* SIZE HARDCODED IN LINKER SCRIPT */
	malloc_init(ALIGN(heap_top, 0x1000), 0x200000);
	driver_init();

	log_info("Hello, world!");
	log_info("We are in the %s() function", __func__);
	log_debug("Allocating 0x100 bytes");
	void *ptr = malloc(0x100);
	log_debug("ptr = %x", ptr);
	log_debug("Freeing 0x100 bytes");
	free(ptr);
	log_info("All Done!");

	puts("\nend of the line\n");
	puts("   ╱|、\n");
	puts("  (˚ˎ 。7\n");
	puts("   |、˜〵\n");
	puts("  じしˍ,)ノ\n");
}

}
