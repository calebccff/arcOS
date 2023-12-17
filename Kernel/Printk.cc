
#include <Arc/memory.h>
#include <Arc/printk.h>

#include <Drivers/UART.h>

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define RESET "\033[0m"


extern "C" {
void puts(const char *str)
{
	g_console->puts(str);
}

void putc(char c)
{
	g_console->putc(c);
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

void putx(uint64_t i)
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


static const char *loglevel_to_string(Loglevel level)
{
	switch (level) {
	case LOGLEVEL_FATAL:
		return "  [" RED    "!!!" RESET "] ";
	case LOGLEVEL_ERROR:
		return "[" RED    "ERROR" RESET "] ";
	case LOGLEVEL_WARN:
		return " [" YELLOW "WARN" RESET "] ";
	case LOGLEVEL_INFO:
		return " [" BLUE   "INFO" RESET "] ";
	case LOGLEVEL_DEBUG:
		return "[" PURPLE "DEBUG" RESET "] ";
	case LOGLEVEL_TEST:
		return " [" PURPLE "TEST" RESET "] ";
	}

	return "[UNKNOWN] ";
}

void vprintk(Loglevel level, const char *fmt, va_list args)
{
	bool is_long = false;
	puts(loglevel_to_string(level));

	while (*fmt) {
		if (*fmt == '%' || is_long) {
			if (!is_long)
				fmt++;
			switch (*fmt) {
			case 's':
				puts(va_arg(args, const char *));
				break;
			case 'c':
				putc(va_arg(args, int32_t));
				break;
			case 'd':
				if (is_long) {
					putl(va_arg(args, int64_t));
					is_long = false;
				} else {
					puti(va_arg(args, int32_t));
				}
				break;
			case 'u':
				if (is_long) {
					putl(va_arg(args, uint64_t));
					is_long	= false;
				} else {
					putu(va_arg(args, uint32_t));
				}
				break;
			case 'x':
				putx(va_arg(args, uint64_t));
				break;
			case 'l':
				is_long = true;
				break;
			case '%':
				putc('%');
				break;
			}
		} else {
			putc(*fmt);
		}
		fmt++;
	}

	putc('\n');
}

void printk(Loglevel level, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintk(level, fmt, args);
	va_end(args);
}

void assert_failed(const char *file, int line, const char *assert, const char *msg)
{
	printk(LOGLEVEL_FATAL, "Assertion failed: %s:%d: '%s' - %s", file, line, assert, msg);
	while (1);
}
