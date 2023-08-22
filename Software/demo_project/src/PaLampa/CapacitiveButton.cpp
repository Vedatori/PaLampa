#include "CapacitiveButton.h"

CapButton::CapButton(const std::vector<int> pinIDs):
    _pinIDs(pinIDs),
    _thresholdOffset(std::vector<float>(pinIDs.size(), _defaultThresholdOffset)),
    _raw(std::vector<uint16_t>(pinIDs.size(), 0)),
    _rawPrev(std::vector<uint16_t>(pinIDs.size(), 0)),
    _rawReference(std::vector<float>(pinIDs.size(), 0.0)),
    _data(std::vector<bool>(pinIDs.size(), 0)) {}

void CapButton::begin() {
    for(int index = 0; index < _pinIDs.size(); ++index) {
        _rawPrev[index] = touchRead(_pinIDs[index]);
        _raw[index] = _rawPrev[index];
        _rawReference[index] = float(getRaw(index));
        _data[index] = 0;
    }
}

void CapButton::update() {
    for(int index = 0; index < _pinIDs.size(); ++index) {
        _rawPrev[index] = _raw[index];
        _raw[index] = touchRead(_pinIDs[index]);

        uint16_t rawFiltered = getRaw(index);

        _data[index] = rawFiltered < (_rawReference[index] - _thresholdOffset[index]);

        if(!_data[index]) {
            _rawReference[index] = _coefIIR * rawFiltered + (1.0 - _coefIIR) * _rawReference[index];
        }
    }
}

void CapButton::setThreshold(int buttonID, float thresholdOffset) {
    if(buttonID < 0 || buttonID >= _pinIDs.size()) {
        printf("Invalid capacitive button ID: %d\n", buttonID);
        return;
    }
    if(thresholdOffset < 0.0){
        printf("Invalid capacitive button threshold offset: %.2f\n", thresholdOffset);
        return;
    }
    _thresholdOffset[buttonID] = thresholdOffset;
}

void CapButton::setThreshold(std::vector<float> threshold) {
    assert(threshold.size() == _pinIDs.size());
    for(int index = 0; index < _pinIDs.size(); ++index) {
        setThreshold(index, _thresholdOffset[index]);
    }
}

uint16_t CapButton::getRaw(int buttonID) const {
    if(buttonID < 0 || buttonID >= _pinIDs.size()) {
        printf("Invalid capacitive button ID: %d\n", buttonID);
        return 0;
    }
    return max(_raw[buttonID], _rawPrev[buttonID]);;
}

float CapButton::getRawReference(int buttonID) const {
    if(buttonID < 0 || buttonID >= _pinIDs.size()) {
        printf("Invalid capacitive button ID: %d\n", buttonID);
        return 0;
    }
    return _rawReference[buttonID];
}

bool CapButton::get(int buttonID) const {
    if(buttonID < 0 || buttonID >= _pinIDs.size()) {
        printf("Invalid capacitive button ID: %d\n", buttonID);
        return false;
    }
    return _data[buttonID];
}

String CapButton::getText() const {
    String out;
    char buffer[16];
    for (int index = 0; index < _pinIDs.size(); ++index) {
        sprintf(buffer, "capBtn%d: %d ", index, _data[index]);
        out = out + String(buffer);
    }
    return out;
}
