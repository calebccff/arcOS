#pragma once

#include <stdarg.h>

typedef enum {
	LOGLEVEL_ERROR,
	LOGLEVEL_WARN,
	LOGLEVEL_INFO,
	LOGLEVEL_DEBUG,
} Loglevel;


#ifndef LOG_DEBUG
#define LOGLEVEL CONFIG_DEFAULT_LOGLEVEL
#else
#define LOGLEVEL LOGLEVEL_DEBUG
#endif

extern "C" {
void vprintk(Loglevel level, const char *fmt, va_list args);
void printk(Loglevel level, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
}

#if LOGLEVEL < LOGLEVEL_DEBUG
#define log_debug(fmt, ...) printk(LOGLEVEL_DEBUG, fmt, ##__VA_ARGS__)
#else
#define log_debug(fmt, ...)
#endif

#if LOGLEVEL < LOGLEVEL_INFO
#define log_info(fmt, ...) printk(LOGLEVEL_INFO, fmt, ##__VA_ARGS__)
#else
#define log_info(fmt, ...)
#endif

#if LOGLEVEL < LOGLEVEL_WARN
#define log_warn(fmt, ...) printk(LOGLEVEL_WARN, fmt, ##__VA_ARGS__)
#else
#define log_warn(fmt, ...)
#endif

#define log_error(fmt, ...) printk(LOGLEVEL_ERROR, fmt, ##__VA_ARGS__)

#define WARN(cond, fmt, ...) do { if (cond) log_warn(fmt, ##__VA_ARGS__); } while (0)
