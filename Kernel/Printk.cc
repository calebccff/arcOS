
#include <Arc/memory.h>
#include <Arc/printk.h>

#include <Drivers/UART.h>

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define RESET "\033[0m"

static const char *loglevel_to_string(Loglevel level)
{
	switch (level) {
	case LOGLEVEL_ERROR:
		return "[" RED "ERROR" RESET "] ";
	case LOGLEVEL_WARN:
		return "[" YELLOW "WARN" RESET "] ";
	case LOGLEVEL_INFO:
		return "[" BLUE "INFO" RESET "] ";
	case LOGLEVEL_DEBUG:
		return "[" PURPLE "DEBUG" RESET "] ";
	}

	return "[UNKNOWN] ";
}

void vprintk(Loglevel level, const char *fmt, va_list args)
{
	puts(loglevel_to_string(level));

	while (*fmt) {
		if (*fmt == '%') {
			fmt++;
			switch (*fmt) {
			case 's':
				puts(va_arg(args, const char *));
				break;
			case 'c':
				putc(va_arg(args, int));
				break;
			case 'd':
				puti(va_arg(args, int));
				break;
			case 'u':
				putu(va_arg(args, uint32_t));
				break;
			case 'x':
				putx(va_arg(args, uint32_t));
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
}

void printk(Loglevel level, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintk(level, fmt, args);
	va_end(args);
}
