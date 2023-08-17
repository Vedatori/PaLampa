#include "CapacitiveButton.h"

CapButton::CapButton(std::vector<int> pinIDs):
    _pinIDs(pinIDs),
    _threshold(std::vector<float>(pinIDs.size(), 2.0f)) {}

void CapButton::begin() {
    for(int i = 0; i < 2; ++i) {
        rawData[i][0] = touchRead(_pinIDs[i]);
        rawData[i][1] = rawData[i][0];
        rawDataIIR[i] = float(getPadRaw(i));
        digitalData[i] = 0;
    }
}

void CapButton::update() {
    for(int i = 0; i < 2; ++i) {
        rawData[i][1] = rawData[i][0];
        rawData[i][0] = touchRead(_pinIDs[i]);

        uint8_t rawFiltered = getPadRaw(i);

        digitalData[i] = rawFiltered < (rawDataIIR[i] - _threshold[i]);

        if(digitalData[i] == false) {
            rawDataIIR[i] = coefIIR*rawFiltered + (1.0 - coefIIR)*rawDataIIR[i];
        }
    }
}

void CapButton::setThreshold(std::vector<float> threshold) {
    assert(threshold.size() == _pinIDs.size());
    for(int i=0; i < threshold.size();i++){
        if(threshold[i] <= 0.0f){
            _threshold[i] = 2.0f;
        } else {
            _threshold[i] = threshold[i];
        }
    }
}

uint16_t CapButton::getPadRaw(int padID) {
    if(padID < 0 || padID > 1) {
        printf("Invalid pad ID: %d\n", padID);
        return 0;
    }
    return max(rawData[padID][0], rawData[padID][1]);;
}

float CapButton::getPadRawIIR(int padID) {
    if(padID < 0 || padID > 1) {
        printf("Invalid pad ID: %d\n", padID);
        return 0;
    }
    return rawDataIIR[padID];
}

bool CapButton::getPadPressed(int padID) {
    if(padID < 0 || padID > 1) {
        printf("Invalid pad ID: %d\n", padID);
        return 0;
    }
    return digitalData[padID];
}
