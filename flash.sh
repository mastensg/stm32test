#!/bin/sh -eu

arm-none-eabi-gdb -ex "target extended :3333" -ex "m" -ex "quit" test.elf
