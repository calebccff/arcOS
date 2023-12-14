#pragma once

#include <Arc/stdint.h>

extern "C" {
void *malloc(size_t size);
void free(void *ptr);
}

#define ALIGN(val, a) (((val) + ((a) - 1)) & ~((a) - 1))
