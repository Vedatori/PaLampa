#include "PaLampa/PaLampa.h"
#include "Arduino.h"

void setup() {
    paLampa.begin();
    paLampa.startWiFiCaptain("<your_name>");
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
    else if (paLampa.buttonRead(0)) {
        paLampa.lights.setWhite(0, potVal);
    }
    else if(paLampa.buttonRead(1)) {
        paLampa.lights.setWhite(1, potVal);
    }
    else if(paLampa.buttonRead(2)) {
        ColorRGB color = {potVal, 0, 0};
        paLampa.lights.setColorPanels(all, color);
    }
    paLampa.printDiagnostics();

    delay(500);
}
