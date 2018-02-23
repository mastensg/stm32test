#!/bin/sh -eu

arm-none-eabi-g++ -std=c++17 \
  -Wall -Wextra -Wpedantic -Wno-main -Wno-unused \
  -ffreestanding -nostdlib \
  -g \
  -c -fno-common -O3 -mcpu=cortex-m3 -mthumb -mfloat-abi=soft \
  src/clock.cc

arm-none-eabi-gcc -std=c11 \
  -Wall -Wextra -Wpedantic -Wno-main -Wno-unused \
  -ffreestanding -nostdlib \
  -g \
  -c -fno-common -O3 -mcpu=cortex-m3 -mthumb -mfloat-abi=soft \
  main.c

arm-none-eabi-ld -Tstm32.ld -nostartfiles -o test.elf main.o clock.o -L /usr/lib/gcc/arm-none-eabi/5.4.1/armv7e-m/softfp/ -lgcc
arm-none-eabi-objcopy -Obinary test.elf test.bin
arm-none-eabi-objdump -d test.elf > test.lst
#cat test.lst
arm-none-eabi-size test.elf
