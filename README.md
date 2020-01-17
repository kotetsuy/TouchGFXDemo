# TouchGFXDemo
I'm trying to run TouchGFX on Nucleo-F412ZG+SPI LCD(https://www.amazon.co.jp/dp/B072N551V3).
I already are a success to run SPI LCD function and SPI TC function independently.

For SPI LCD is as;
- SPILCDTest
- SPILCDTestFPS
- SPILCDTestXY

For SPI TC is as;
- TouchTest
- TouchTestHW

# Trying
I'm developing as;
- GUITestNoOS

It's not working now.

# Hardware Connection
| Pinname | Function |
|---|---|
|PC6|DC|
|PB8|LED|
|PB15|RESET|
|PA5|LCD SCK|
|PA6|LCD MISO|
|PA7|LCD MOSI|
|PD14|LCD CS|
|PB5|TS MOSI|
|PB3|TS SCK|
|PB4|TS MISO|
|PE9|TS CS|
|PE13|TS IRQ|

![Neucle and SPI LCD](https://github.com/kotetsuy/TouchGFXDemo/tree/master/images/IMG_1484.jpg "Picture")

# TODO
I'm going to support QSPI board to support bitmap on TouchGFX.
