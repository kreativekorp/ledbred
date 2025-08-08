# ledbred
Led·Bred

## Bill of Materials
* 1x [Arduino Mega 2560 R3](https://store.arduino.cc/products/arduino-mega-2560-rev3) or compatible clone
* 1x [Screw Terminal Shield](https://www.adafruit.com/product/196)
* 1x [MicroSD Shield](https://www.adafruit.com/product/1141)
* 3x [32x8 NeoPixel RGB LED Matrix](https://www.adafruit.com/product/2294) (no longer stocked by Adafruit but clones can be found easily)
* 1x [Breadboard-Friendly NeoPixel RGB LED](https://www.adafruit.com/product/1312)
* 1x [Rotary Encoder with Pushbutton](https://www.adafruit.com/product/377)
* 1x [Monochrome 128x32 SPI OLED Display](https://www.adafruit.com/product/661)
* 1x [HB15CKW01-5F-FB Illuminated Pushbutton](https://www.digikey.com/en/products/detail/nkk-switches/HB15CKW01-5F-FB/1056630)
* 1x [TEPT4400 Photodiode](https://www.digikey.com/en/products/detail/vishay-semiconductor-opto-division/TEPT4400/1681191)
* 1x [Lamping Tool](https://www.digikey.com/en/products/detail/nkk-switches/AT111/1050064) (highly recommended)
* 1x [1MΩ Through-Hole Resistor](https://www.digikey.com/en/products/detail/stackpole-electronics-inc/CF14JT1M00/1741316)

## Constructing the pen
1. Use the lamping tool to replace the LED in the illuminated pushbutton with the TEPT4400 photodiode.
2. Blacken the side of the illuminated pushbutton's cap with a Sharpie. (This keeps out ambient light to improve detection.)
3. Solder the illuminated pushbutton to the light pen cable.
4. Install the illuminated pushbutton in the light pen top cap (`pencap1.stl`).
5. Feed the light pen cable through the light pen barrel (`penbarrel.stl`).
6. Feed the light pen cable through the light pen bottom cap (`pencap2.stl`).
7. Push the end caps into the barrel.

## Wiring Diagram
![](fritzing/ledbred_bb.png)

## Wiring Connections
* Rotary encoder left pin to Arduino D2
* Rotary encoder center pin to GND
* Rotary encoder right pin to Arduino D3
* Rotary encoder switch pin 1 to Arduino D4
* Rotary encoder switch pin 2 to GND
* Illuminated pushbutton switch pin 1 to Arduino D5
* Illuminated pushbutton switch pin 2 to GND
* Top RGB LED matrix DATA IN to Arduino D6
* Center RGB LED matrix DATA IN to Arduino D7
* Bottom RGB LED matrix DATA IN to Arduino D8
* Individual RGB LED DATA IN to Arduino D9
* OLED DATA/MOSI to Arduino D11
* OLED CLK/SCK to Arduino D13
* OLED CS to Arduino A3
* OLED D/C to Arduino A2
* OLED RST to Arduino A1
* Illuminated pushbutton LED anode to Arduino A0
* Illuminated pushbutton LED anode to 1MΩ resistor
* 1MΩ resistor to VCC
* Illuminated pushbutton LED cathode to GND
