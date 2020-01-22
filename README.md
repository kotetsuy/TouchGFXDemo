# TouchGFXDemo
I try to run TouchGFX on Nucleo-F412ZG+SPI LCD(https://www.amazon.co.jp/dp/B072N551V3).
I already are a success it.

For SPI LCD is as;
- SPILCDTest (For F446)
- SPILCDTestFPS (For F446)
- SPILCDTestXY (For F446)
- SPILCDTestFPS412 (For F412)

For SPI TC is as;
- TouchTest (For F446)
- TouchTestHW (For F446)
- TouchTestHW412 (For F412)

For Combination test is as;
- DrawingTest (For F412)

For small GUI by TouchGFX test as;
- GUITestNoOS (For F412)
https://youtu.be/tz8haqRtUfs

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

![Nucleo and SPI LCD](https://github.com/kotetsuy/TouchGFXDemo/blob/master/images/IMG_1484.jpg)

# TODO
I'm going to support QSPI board to support bitmap on TouchGFX.
