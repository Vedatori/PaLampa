#include "Photoresistor.h"

Photoresistor::Photoresistor(std::vector<int> pinIDs) : 
    _pinIDs(pinIDs),
    _rawData(std::vector<int>(pinIDs.size(), 0)) {}

void Photoresistor::update() {
    for (int photoresID = 0; photoresID < _pinIDs.size(); ++photoresID) {
        _rawData[photoresID] = analogRead(_pinIDs[photoresID]);
    }
}

int Photoresistor::getRaw(const int photoresID) const {
    if (photoresID < 0 || photoresID >= _pinIDs.size()) {
        printf("Invalid photores ID: %d\n", photoresID);
        return 0;
    }
    return _rawData[photoresID];
}

float Photoresistor::get(const int photoresID) const {
    if (photoresID < 0 || photoresID >= _pinIDs.size()) {
        printf("Invalid photores ID: %d\n", photoresID);
        return 0;
    }
    return float(_rawData[photoresID])/4095.0;
}

String Photoresistor::getText() const {
    String out;
    char buffer[16];
    for (int photoresID = 0; photoresID < _pinIDs.size(); ++photoresID) {
        sprintf(buffer, "photo%d: %.2f ", photoresID, get(photoresID));
        out = out + String(buffer);
    }
    return out;
}
