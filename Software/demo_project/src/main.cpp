#include "PaLampa/PaLampa.h"
#include "Arduino.h"

bool prevCapBtnState = false;
bool whiteOn = false;
float whiteBrightness = 0.0;
float whiteMix = 0.0;
float colorRed, colorGreen, colorBlue;
ColorRGB color = black;

void setup() {
    paLampa.begin();
    paLampa.startWiFiCaptain("<your_name>");
    paLampa.oled.sendClear();
    paLampa.lights.setColorTransition(all, Exponential, 2.0);
    paLampa.lights.setWhiteTransition({1, 1}, Exponential, 2.0);
}

void loop() {
    float potVal = paLampa.potentiometerRead();
    if(paLampa.buttonRead(0) && paLampa.buttonRead(1)){
        paLampa.piezo.playMelody(themeMelody);
    }
    else if(paLampa.buttonRead(0) && paLampa.buttonRead(2)) {
        ESP.restart();
    }
    else if(paLampa.buttonRead(1) && paLampa.buttonRead(2)) {
        color.blue = potVal;
    }
    else if (paLampa.buttonRead(0)) {
        whiteMix = potVal;
    }
    else if(paLampa.buttonRead(1)) {
        color.red = potVal;
    }
    else if(paLampa.buttonRead(2)) {
        color.green = potVal;
    }
    else {
        whiteBrightness = potVal;
    }

    bool newCapBtnState = paLampa.capButton.getPadPressed(0);
    if(newCapBtnState != prevCapBtnState) {
        prevCapBtnState = newCapBtnState;
        if(newCapBtnState) {
            whiteOn = !whiteOn;
        }
    }
    if(whiteOn == false) {
        whiteBrightness = 0.0;
    }

    paLampa.lights.setWhiteMix(whiteBrightness, whiteMix);
    paLampa.lights.setColorPanels(all, color);

    static uint prevDiagTime = 0;
    if(millis() > prevDiagTime + 1000) {
        prevDiagTime = millis();
        paLampa.printDiagnostics();
    }

    delay(100);
}
