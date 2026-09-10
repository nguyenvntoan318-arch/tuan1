CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
CFLAGS = -mcpu=cortex-m3 -mthumb -std=c11 -Os -g3 -Wall -Wextra -Werror -ffreestanding -ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables
LDFLAGS = -nostdlib -Wl,--gc-sections -Wl,-Map=build/bai04.map -T stm32f103c8.ld

.PHONY: all clean flash
all: build/bai04.bin

build:
	mkdir -p build

build/main.o: main.c button.h | build
	$(CC) $(CFLAGS) -c main.c -o $@

build/startup.o: startup.s | build
	$(CC) -mcpu=cortex-m3 -mthumb -g3 -c startup.s -o $@

build/bai04.elf: build/main.o build/startup.o stm32f103c8.ld
	$(CC) -mcpu=cortex-m3 -mthumb $(LDFLAGS) build/main.o build/startup.o -lgcc -o $@
	$(SIZE) $@

build/bai04.bin: build/bai04.elf
	$(OBJCOPY) -O binary $< $@

flash: build/bai04.bin
	st-flash --reset write build/bai04.bin 0x08000000

clean:
	rm -rf build
