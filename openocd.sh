#!/bin/sh -eu

#openocd \
#    -f /usr/share/openocd/scripts/interface/stlink-v2.cfg \
#    -f /usr/share/openocd/scripts/target/stm32f1x.cfg \
#    -f "$(pwd)/hardware_reset.cfg"
#exit

openocd \
    -f /usr/share/openocd/scripts/interface/stlink-v2.cfg \
    -f /usr/share/openocd/scripts/target/stm32f1x.cfg
