# HW Designer's notes
## I2C addresses
+ OLED Display - `0x3C`
+ FUSB302 - `0x22`

## Current consumptions
+ Board's idle current consumption (with overhead) - ESP and OLED running, no LEDs - 150 - 200 mA
+ WW or CW string at 100% duty (without board's idle consumption) - 1400mA, the current consumption is approximately linear with the PWM duty cycle



## Misc
+ Potentiometer is wired backwards (eg. ADC value decreases when turning counter clockwise) - change it in the next Rev or in SW
+ Current sense resistor in the CC LED driver was probably DoA, check who's fault it was, maybye use 1206 reistors for current spikes from charged capacitors when connecting LEDs to running driver
+ Some LEDs were not soldered correctly - there is probably nothing I can do about it, just beware.
+ Change WW pin to IO17 (Pin 28), internal pullup on IO5 caused short flash on startup / ESP reset. The situation is much better on GPIO17, but for some reason the WW strings still flash on startup (but not on ESP rst, which is weird, might look into it later with more boards assembled).
+ Add JST for Neopixel
+ New Vedatori Logo

## 17.05.2023 - Developer's meeting
+ Add temperature measurement to LED board
+ Add milled grooves to LED board edges for better cooling
+ Add JST 3 pin for neopixel LEDs onto mainboard and create new Neopixel channel
+ Move one photoresistor to the back, switch it with the electrolytic capacitor, move the second photoresistor somewhere near
+ Add "do not remove while running" text near connectors 
+ Add 2 pin JST for touch
