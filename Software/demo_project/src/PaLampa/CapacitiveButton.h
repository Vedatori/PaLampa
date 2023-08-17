#pragma once

#include "Arduino.h"
#include <vector>

const int TOUCH_PIN[2] = {12, 14};

class CapButton {
    std::vector<int> _pinIDs;
    std::vector<float> _threshold;

    uint16_t rawData[2][2]; //Pin, last[1]/current[0] button state
    float rawDataIIR[2];
    bool digitalData[2];
    float coefIIR = 0.01;
public:
    CapButton(std::vector<int> pinIDs);  // std::vector<float> threshold
    void begin();
    void update();
    void setThreshold(std::vector<float> threshold);
    uint16_t getPadRaw(int padID);
    float getPadRawIIR(int padID);
    bool getPadPressed(int padID);
    bool getPressed(int buttonID);
    int getPressedIndex();
};
