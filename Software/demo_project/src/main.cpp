#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
    paLampa.startWiFiCaptain("<your_name>");
    paLampa.lights.setTransition(all, Exponential, 2.0);
}

void loop() {
    float potVal = paLampa.potentiometerRead();
    if (paLampa.buttonRead(0)) {
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
