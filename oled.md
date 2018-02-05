ssd1306
=======

    D0  SCLK
    D1  SDIN
    DC  Data/Command

--------------------------

https://github.com/guyc/py-gaugette/blob/master/gaugette/ssd1306.py

    # Device name will be /dev/spidev-{bus}.{device}
    # dc_pin is the data/commmand pin.  This line is HIGH for data, LOW for command.
    # We will keep d/c low and bump it high only for commands with data
    # reset is normally HIGH, and pulled LOW to reset the display

--------------------------

See also
--------

- http://guy.carpenter.id.au/gaugette/2012/11/08/controlling-an-adafruit-spi-oled-with-a-raspberry-pi/
- https://learn.adafruit.com/monochrome-oled-breakouts
- https://github.com/guyc/py-gaugette/blob/master/samples/ssd1306_test.py
- https://github.com/adafruit/Adafruit_SSD1306/blob/master/examples/ssd1306_128x64_spi/ssd1306_128x64_spi.ino
- https://github.com/jandelgado/arduino/wiki/SSD1306-based-OLED-connected-to-Arduino
