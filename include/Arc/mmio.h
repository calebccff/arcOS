#pragma once

#include <Arc/stdint.h>

#define writel(val, addr) (*(volatile uint32_t *)(addr) = (val))
#define writeb(val, addr) (*(volatile uint8_t *)(addr) = (val))

#define readl(addr) (*(volatile uint32_t *)(addr))
#define readb(addr) (*(volatile uint8_t *)(addr))
