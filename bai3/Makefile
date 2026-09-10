CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -O1 -Wall -g -nostdlib

all: firmware.bin

firmware.elf: main.c startup.c
	$(CC) $(CFLAGS) -T linker.ld main.c startup.c -o firmware.elf

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary firmware.elf firmware.bin

flash: firmware.bin
	st-flash write firmware.bin 0x8000000

clean:
	rm -f *.o *.elf *.bin
