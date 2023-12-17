#pragma once

#include <Arc/stdint.h>

extern "C" {
void *malloc(size_t size);
void free(void *ptr);

static inline void memset(void *ptr, uint8_t val, size_t size) {
	for (size_t i = 0; i < size; i++) {
		((uint8_t *) ptr)[i] = val;
	}
}

void test_malloc();
}

#define ALIGN(val, a) (((val) + ((a) - 1)) & ~((a) - 1))
