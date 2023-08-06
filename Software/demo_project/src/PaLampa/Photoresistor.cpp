#include "Photoresistor.h"

Photoresistor::Photoresistor(std::vector<int> pinIDs) : 
    _pinIDs(pinIDs),
    _rawData(std::vector<int>(pinIDs.size(), 0)) {}

void Photoresistor::update() {
    for (int index = 0; index < _pinIDs.size(); ++index) {
        _rawData[index] = analogRead(_pinIDs[index]);
    }
}

int Photoresistor::getRaw(const int index) const {
    if (index < 0 || index >= _pinIDs.size()) {
        printf("Invalid photores ID: %d\n", index);
        return 0;
    }
    return _rawData[index];
}

float Photoresistor::get(const int index) const {
    if (index < 0 || index >= _pinIDs.size()) {
        printf("Invalid photores ID: %d\n", index);
        return 0;
    }
    return float(_rawData[index])/4095.0;
}

String Photoresistor::getText() const {
    String out;
    char buffer[16];
    for (int index = 0; index < _pinIDs.size(); ++index) {
        sprintf(buffer, "photo%d: %.2f ", index, get(index));
        out = out + String(buffer);
    }
    return out;
}
