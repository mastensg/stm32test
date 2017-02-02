#!/bin/sh -eu

./breathe.py > breathe.h

arm-none-eabi-gcc -std=c11 \
  -Wall -Wextra -Wno-main \
  -ffreestanding -nostdlib \
  -g \
  -c -fno-common -O0 -mcpu=cortex-m3 -mthumb \
  main.c

arm-none-eabi-ld -Tstm32.ld -nostartfiles -o test.elf main.o
arm-none-eabi-objcopy -Obinary test.elf test.bin
arm-none-eabi-objdump -d test.elf > test.lst
arm-none-eabi-size test.elf
