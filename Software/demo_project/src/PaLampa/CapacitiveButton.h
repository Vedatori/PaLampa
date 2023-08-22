#pragma once

#include "Arduino.h"
#include <vector>

class CapButton {
    const float _defaultThresholdOffset = 5.0;
    const float _coefIIR = 0.01;

    const std::vector<int> _pinIDs;
    std::vector<float> _thresholdOffset;
    std::vector<uint16_t> _raw;
    std::vector<uint16_t> _rawPrev;
    std::vector<float> _rawReference;
    std::vector<bool> _data;

public:
    CapButton(const std::vector<int> pinIDs);
    void begin();
    void update();
    void setThreshold(int buttonID, float threshold);
    void setThreshold(std::vector<float> threshold);
    uint16_t getRaw(int buttonID) const;
    float getRawReference(int buttonID) const;
    bool get(int buttonID) const;
    String getText() const;
};
