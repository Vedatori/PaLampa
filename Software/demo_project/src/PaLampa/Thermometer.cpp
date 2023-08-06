#include "Thermometer.h"

Thermometer::Thermometer(std::vector<int> pinIDs) : 
    _pinIDs(pinIDs),
    _data(std::vector<float>(pinIDs.size(), 0.0)) 
{
    for (int index = 0; index < _pinIDs.size(); ++index) {
        _oneWire.emplace_back(_pinIDs[index]);
    }
    for (int index = 0; index < _pinIDs.size(); ++index) {
        _dallasTemp.emplace_back(&_oneWire[index]);
    }
}

void Thermometer::update() {
    for (int index = 0; index < _pinIDs.size(); ++index) {
        _dallasTemp[index].requestTemperatures();
        float newTemp = _dallasTemp[index].getTempCByIndex(0);
        if(newTemp > -100.0) {
            // Filter out nonsense measurements
            _data[index] = newTemp;
        }
    }
}

float Thermometer::get(const int index) const {
    if (index < 0 || index >= _pinIDs.size()) {
        printf("Invalid photores ID: %d\n", index);
        return 0;
    }
    return _data[index];
}

String Thermometer::getText() const {
    String out;
    char buffer[16];
    for (int index = 0; index < _pinIDs.size(); ++index) {
        sprintf(buffer, "temp%d: %.1f ", index, _data[index]);
        out = out + String(buffer);
    }
    return out;
}
