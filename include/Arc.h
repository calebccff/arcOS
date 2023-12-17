#pragma once

#include <Arc/maths.h>

void assert_failed(const char *file, int line, const char *assert, const char *msg);

#define bug(x, fmt, ...) do { \
	if (!(x)) { \
		printk(LOGLEVEL_FATAL, "%s:%d: " #fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
		while (1); \
	} \
} while (0)

#define assert(x) do { if (!(x)) assert_failed(__FILE__, __LINE__, #x, ""); } while (0)

