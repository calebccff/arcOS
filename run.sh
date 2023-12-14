#!/bin/sh
set -e

# Parse options (-d = debug)
while getopts "d" opt; do
	case $opt in
		d)
			DEBUG="-s -S"
			;;
	esac
done

shift $((OPTIND-1))

echo "Press Ctrl+a -> x to quit"
qemu-system-aarch64 -M virt \
	-cpu cortex-a53 \
	-nographic \
	-smp cpus=4 \
	$DEBUG \
	-kernel build/Arc.elf $@
