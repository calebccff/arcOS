#pragma once

#include <Drivers/Core.h>

struct Console {
	char fifo_size;
	void (*puts)(const char *str);
	void (*putc)(char c);
	char (*getc)();
};

extern Console *g_console;
