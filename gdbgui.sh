#!/bin/sh -eu

# https://gdbgui.com/downloads.html
# pip3 install --user --upgrade gdbgui

#gdbgui -g /usr/bin/arm-none-eabi-gdb -ex "target extended :3333" test.elf
gdbgui -g /usr/bin/arm-none-eabi-gdb test.elf
