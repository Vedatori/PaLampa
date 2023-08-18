#pragma once

#include "Arduino.h"
#include <FUSB302.h>

enum PowerMode {
    Low_1000mA = 0,
    Medium_1500mA = 1,
    High_3000mA = 2,
};

extern FUSB302 usbc;

class USB_C_power_module {
    PowerMode _mode = Low_1000mA;
public:
    void begin();
    PowerMode getMode();
    float getLimitA();
};
