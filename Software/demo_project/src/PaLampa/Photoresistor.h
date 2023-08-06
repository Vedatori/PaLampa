#pragma once

#include <vector>
#include "Arduino.h"

class Photoresistor {
    std::vector<int> _pinIDs;
    std::vector<int> _rawData;
public:
    Photoresistor(std::vector<int> pinIDs);
    void update();
    int getRaw(const int index) const;
    float get(const int index) const;
    String getText() const;
};
