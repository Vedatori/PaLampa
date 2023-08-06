#pragma once

#include <vector>
#include "Arduino.h"
#include "OneWire.h"
#include "DallasTemperature.h"

class Thermometer {
    std::vector<int> _pinIDs;
    std::vector<float> _data;
    std::vector<OneWire> _oneWire;
    std::vector<DallasTemperature> _dallasTemp;
public:
    Thermometer(std::vector<int> pinIDs);
    void update();
    float get(const int thermometerID) const;
    String getText() const;
};
