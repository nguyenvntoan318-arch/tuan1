CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -nostdlib
LDFLAGS = -T linker.ld

all: stm32_b1.bin

stm32_b1.elf: main.c startup.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

stm32_b1.bin: stm32_b1.elf
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -f *.elf *.bin

flash: stm32_b1.bin
	st-flash write stm32_b1.bin 0x8000000
