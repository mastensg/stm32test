#!/bin/sh -eu

cgdb -d arm-none-eabi-gdb -ex "target extended :3333" test.elf
