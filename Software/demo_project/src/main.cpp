#include "Arduino.h"

#include "Adafruit_NeoPixel.h"

#include "PaLampa/PaLampa.h"

const int POT_PIN = 36;
const int LED_WARM_PIN = 5, LED_WARM_CHANNEL = 0;
const int LED_COLD_PIN = 17, LED_COLD_CHANNEL = 1;
const int LED_FREQ = 20000, LED_RESOLUTION_BIT = 10;
const int LED_RGB_PIN = 16;
const int LED_RGB_COUNT = 16;

Adafruit_NeoPixel pixels(LED_RGB_COUNT, LED_RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    PaLampa.begin();
    ledcSetup(LED_WARM_CHANNEL, LED_FREQ, LED_RESOLUTION_BIT);
    ledcSetup(LED_COLD_CHANNEL, LED_FREQ, LED_RESOLUTION_BIT);
    ledcAttachPin(LED_WARM_PIN, LED_WARM_CHANNEL);
    ledcAttachPin(LED_COLD_PIN, LED_COLD_CHANNEL);

    Serial.begin(115200);
    pixels.begin();
}

void loop() {
    int potVal = 4095 - analogRead(POT_PIN);
    if (PaLampa.buttonRead(0)) {
        ledcWrite(LED_WARM_CHANNEL, potVal / 4);
    }
    else if(PaLampa.buttonRead(1)) {
        ledcWrite(LED_COLD_CHANNEL, potVal / 4);
    }
    else if(PaLampa.buttonRead(2)) {
        uint32_t color = pixels.Color(potVal / 16, potVal / 16, potVal / 16);
        for(uint8_t ledID = 0; ledID < LED_RGB_COUNT; ++ledID) {
            pixels.setPixelColor(ledID, color);
        }
        pixels.show();
    }
    
    PaLampa.printDiagnostics();

    delay(500);
}