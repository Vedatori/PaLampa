# HW Designer's notes
## I2C addresses
+ OLED Display - `0x3C`
+ FUSB302 - `0x22`

## Misc
+ Potentiometer is wired backwards (eg. ADC value decreases when turning counter clockwise) - change it in the next Rev or in SW
+ Current sense resistor in the CC LED driver was probably DoA, check who's fault it was, maybye use 1206 reistors for current spikes from charged capacitors when connecting LEDs to running driver
+ Some LEDs were not soldered correctly - there is probably nothing I can do about it, just beware.
+Change WW PWM pin to IO17, IO5 has internal pullup and probably causes short flash during power on/ ESP reset/ ESP flashing.aa