#!/bin/sh -eu

arm-none-eabi-gdb -ex "target extended :3333" test.elf
