#pragma once

#include <Arc/stdint.h>

void driver_init();

extern "C" {
void puts(const char *str);
void putc(char c);
void puti(int i);
void putu(uint32_t i);
void putl(long i);
void putx(uint32_t i);
}
