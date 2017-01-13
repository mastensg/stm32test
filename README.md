STM32F103C8T6

How to flash
------------

In terminal one:

    ./openocd.sh

In terminal two:

    ./gdb.sh

In GDB:

    make
    monitor reset halt
    load
    monitor reset run

See also
--------

- http://www.chinalctech.com/index.php?_m=mod_product&_a=view&p_id=1029
- http://www.jtagtest.com/pinouts/arm20
- http://www.triplespark.net/elec/pdev/arm/stm32.html
- https://github.com/bjornfor/stm32-test/
- http://processors.wiki.ti.com/index.php/Linker_Command_File_Primer
