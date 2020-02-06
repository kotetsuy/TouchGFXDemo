# TouchGFXDemo
I try to run TouchGFX on Nucleo-F412ZG + SPI LCD(https://www.amazon.co.jp/dp/B072N551V3) + QSPI FLASH(https://ja.aliexpress.com/item/33035168600.html).
I'm already a success it.
SPI LCD is ILI9341+XPT2048. QSPI FLASH is W25Q128JV.

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

For QSPI test as;
- QSPI test (For F412)

For big GUI by TouchGFX as;
- TouchGFXDemo (For F412)
https://youtu.be/MUmIVOVB6cI

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
|PD12|QSPI IO1|
|PD11|QSPI IO0|
|PB2|QSPI CLK|
|PB6|QSPI CS|
|PE2|QSPI IO2|
|PD13|QSPI IO3|

![Nucleo and SPI LCD](https://github.com/kotetsuy/TouchGFXDemo/blob/master/images/IMG_1556.jpg)

# Related project

*.stldr for flash W25Q128JV.

https://github.com/kotetsuy/STLDR
