#!/bin/sh
set -e

qemu-system-aarch64 -M virt \
	-cpu cortex-a53 \
	-nographic \
	-kernel build/Arc.elf