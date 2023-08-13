#include "PaLampa/PaLampa.h"

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
       ColorRGB color = {potVal*255.0, 0, 0};
       //paLampa.lights.setColor(0, 0, color);
       paLampa.lights.setColorPanels(all, color);
    }
    
    paLampa.printDiagnostics();

    delay(500);
}
