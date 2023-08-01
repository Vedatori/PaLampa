#ifndef _PHOTORESISTOR_
#define _PHOTORESISTOR_

#include "Arduino.h"
#include <vector>

class Photoresistor {
    std::vector<int> _pinIDs;
    std::vector<int> _rawData;
public:
    Photoresistor(std::vector<int> pinIDs);
    void update();
    int getRaw(const int photoresID) const;
    float get(const int photoresID) const;
    String getText() const;
};

#endif // _PHOTORESISTOR_