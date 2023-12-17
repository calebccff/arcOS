// PL011 UART driver
#include <Arc/mmio.h>

#include <Drivers/UART.h>

#define UARTDR 0x09000000

static void pl011_putc(char c) {
	writeb(c, UARTDR);
}

static void pl011_puts(const char *str) {
	while (*str)
		pl011_putc(*str++);
}

static char pl011_getc() {
	return readb(UARTDR) & 0xFF;
}

static Console pl011_console = {
	.fifo_size = 1,
	.puts = pl011_puts,
	.putc = pl011_putc,
	.getc = pl011_getc,
};

Console *g_console = &pl011_console;
