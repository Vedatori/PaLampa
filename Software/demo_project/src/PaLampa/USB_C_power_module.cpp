#include "USB_C_power_module.h"

void USB_C_power_module::begin() {
    update();
}

void USB_C_power_module::setMode(PowerMode newMode) {
    mode = newMode;
}

PowerMode USB_C_power_module::getMode() {
    return mode;
}

void USB_C_power_module::update() {
    ;
}

float USB_C_power_module::getLimitA() {
    switch(mode) {
        case USB2_500mA:
            return 0.5;
        case USB3_900mA:
            return 0.9;
        case Medium_1500mA:
            return 1.5;
        case High_3000mA:
            return 3.0;
        case Automatic: {
            return 0.9;
        }
        default:
            mode = USB2_500mA;
            return 0.5;
    }
}