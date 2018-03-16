#!/bin/sh -eu

arm-none-eabi-gdb \
    -ex "target extended :3333" \
    -ex "monitor reset halt" \
    -ex "load" \
    -ex "monitor reset run" \
    -ex "quit" \
    build/test.elf
