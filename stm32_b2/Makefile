TARGET = firmware
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb -O1 -Wall -g -nostdlib -T linker.ld
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET).bin

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

flash: $(TARGET).bin
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(TARGET).elf verify reset exit"

clean:
	rm -f *.o *.elf *.bin
