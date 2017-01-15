#!/bin/sh

# Any dependencies not in the Debian base install that are not contained in
# this Git repository should be listed in this install script.

apt-get -y install \
    binutils-arm-none-eabi \
    gcc-arm-none-eabi \
    gdb-arm-none-eabi \
    make \
    openocd \
    python3
