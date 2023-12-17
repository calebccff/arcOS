#pragma once

#include <config.h>
#include <Arc/stdint.h>
#include <stdarg.h>

typedef enum {
	LOGLEVEL_FATAL,
	LOGLEVEL_ERROR,
	LOGLEVEL_WARN,
	LOGLEVEL_INFO,
	LOGLEVEL_DEBUG,
	LOGLEVEL_TEST,
} Loglevel;


#ifndef LOG_DEBUG
#define LOGLEVEL CONFIG_DEFAULT_LOGLEVEL
#else
#define LOGLEVEL LOGLEVEL_DEBUG
#endif

extern "C" {
void vprintk(Loglevel level, const char *fmt, va_list args);
void printk(Loglevel level, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

void puts(const char *str);
void putc(char c);
void puti(int i);
void putu(uint32_t i);
void putl(long i);
void putx(uint64_t i);
}

#if LOGLEVEL >= LOGLEVEL_TEST
#define log_test(fmt, ...) printk(LOGLEVEL_TEST, fmt, ##__VA_ARGS__)
#define log_test_start(name) log_test("    === Testing %s", name)
#define log_test_end(name) printk(LOGLEVEL_TEST, "    === Test %s passed", name)
#else
#define log_test(fmt, ...)
#define log_test_start(name)
#define log_test_end(name)
#endif

#if LOGLEVEL >= LOGLEVEL_DEBUG
#define log_debug(fmt, ...) printk(LOGLEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define log_debugfn(fmt, ...) printk(LOGLEVEL_DEBUG, "%s(" fmt ")", __func__, ##__VA_ARGS__)
#else
#define log_debug(fmt, ...)
#endif

#if LOGLEVEL >= LOGLEVEL_INFO
#define log_info(fmt, ...) printk(LOGLEVEL_INFO, fmt, ##__VA_ARGS__)
#define log_infofn(fmt, ...) printk(LOGLEVEL_INFO, "%s(" fmt ")", __func__, ##__VA_ARGS__)
#else
#define log_info(fmt, ...)
#define log_infofn(fmt, ...)
#endif

#if LOGLEVEL >= LOGLEVEL_WARN
#define log_warn(fmt, ...) printk(LOGLEVEL_WARN, fmt, ##__VA_ARGS__)
#define log_warnfn(fmt, ...) printk(LOGLEVEL_WARN, "%s(" fmt ")", __func__, ##__VA_ARGS__)
#else
#define log_warn(fmt, ...)
#define log_warnfn(fmt, ...)
#endif

#define log_error(fmt, ...) printk(LOGLEVEL_ERROR, fmt, ##__VA_ARGS__)
#define log_errorfn(fmt, ...) printk(LOGLEVEL_ERROR, "%s(" fmt ")", __func__, ##__VA_ARGS__)

#define WARN(cond, fmt, ...) do { if (cond) log_warn(fmt, ##__VA_ARGS__); } while (0)
