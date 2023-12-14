
#include <Drivers/Core.h>
#include <Drivers/UART.h>

extern "C" {
void puts(const char *str)
{
	g_console->puts(str);
}

void putc(char c)
{
	g_console->puts(&c);
}

// FIXME: can't handle negative?
void puti(int i)
{
	char buf[32];
	char *p = buf + 31;
	*p = 0;
	do {
		*--p = '0' + (i % 10);
		i /= 10;
	} while (i);
	puts(p);
}

void putu(uint32_t i)
{
	char buf[32];
	char *p = buf + 31;
	*p = 0;
	do {
		*--p = '0' + (i % 10);
		i /= 10;
	} while (i);
	puts(p);
}

void putl(long i)
{
	char buf[32];
	char *p = buf + 31;
	*p = 0;
	do {
		*--p = '0' + (i % 10);
		i /= 10;
	} while (i);
	puts(p);
}

void putx(uint32_t i)
{
	char buf[32];
	char *p = buf + 31;
	*p = 0;
	do {
		*--p = "0123456789abcdef"[i & 0xf];
		i >>= 4;
	} while (i);
	puts(p);
}

}
