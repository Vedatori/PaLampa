#include "Arduino.h"

#include "PaLampa/PaLampa.h"

//Adafruit_NeoPixel pixels(LED_RGB_COUNT, LED_RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    paLampa.begin();

    Serial.begin(115200);
}

void loop() {
    float potVal = paLampa.potentiometerRead();
    if (paLampa.buttonRead(0)) {
        paLampa.lights.setWarm(potVal);
    }
    else if(paLampa.buttonRead(1)) {
        paLampa.lights.setCold(potVal);
    }
    else if(paLampa.buttonRead(2)) {
        /*uint32_t color = pixels.Color(potVal / 16, potVal / 16, potVal / 16);
        for(uint8_t ledID = 0; ledID < LED_RGB_COUNT; ++ledID) {
            pixels.setPixelColor(ledID, color);
        }
        pixels.show();
        */
       //paLampa.lights.setColor({potVal*255, 0, 0});
    }
    
    paLampa.printDiagnostics();

    delay(500);
}
