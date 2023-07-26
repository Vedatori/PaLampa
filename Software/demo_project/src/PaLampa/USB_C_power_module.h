#ifndef _USB_C_POWER_MODULE_
#define _USB_C_POWER_MODULE_

#include "Arduino.h"

enum PowerMode {
    USB2_500mA = 0,
    USB3_900mA = 1,
    Medium_1500mA = 2,
    High_3000mA = 3,
    Automatic = 4
};

class USB_C_power_module {

    PowerMode mode = Automatic;

public:
    void begin();
    void setMode(PowerMode mode);
    PowerMode getMode();
    void update();
    float getLimitA();
};

#endif // _USB_C_POWER_MODULE_