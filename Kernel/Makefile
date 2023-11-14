osname := $(shell uname -s)

CROSS_PREFIX = aarch64-linux-gnu-

all: Arc.elf

init.o: init.c
	$(CROSS_PREFIX)gcc -c $< -o $@

startup.o: Startup.s
	$(CROSS_PREFIX)as -c $< -o $@

Arc.elf: init.o startup.o
	$(CROSS_PREFIX)ld -Tarm64.ld $^ -o $@

Arc.bin: init.elf
	$(CROSS_PREFIX)objcopy -O binary $< $@

clean:
	rm -f Arc.bin Arc.elf startup.o init.o