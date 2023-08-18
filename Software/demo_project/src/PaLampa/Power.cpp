#include "Power.h"

FUSB302 usbc;

void USB_C_power_module::begin() {
    usbc.init();
    
    int cc1_meas, cc2_meas;
    usbc.detect_cc_pin_sink(&cc1_meas, &cc2_meas);

    if(cc1_meas == TYPEC_CC_VOLT_OPEN && cc2_meas == TYPEC_CC_VOLT_OPEN) {
        printf("Power detect: both CC pins open.\n");
    }
    else if(cc1_meas != TYPEC_CC_VOLT_OPEN && cc2_meas != TYPEC_CC_VOLT_OPEN) {
        printf("Power detect: both CC pins non-open.\n");
    }
    else if(cc1_meas > TYPEC_CC_VOLT_SNK_3_0 || cc2_meas > TYPEC_CC_VOLT_SNK_3_0) {
        printf("Power detect: at least one CC pin undefined.\n");
    }
    else {
        int max_meas = max(cc1_meas, cc2_meas);
        switch(max_meas) {
            case TYPEC_CC_VOLT_OPEN :
            case TYPEC_CC_VOLT_RA :
            case TYPEC_CC_VOLT_RD :
            case TYPEC_CC_VOLT_SNK_DEF :
                _mode = Low_1000mA;
                break;
            case TYPEC_CC_VOLT_SNK_1_5 :
                _mode = Medium_1500mA;
                break;
            case TYPEC_CC_VOLT_SNK_3_0 :
                _mode = High_3000mA;
                break;
            default :
                _mode = Low_1000mA;
            break;
        }
    }
}

PowerMode USB_C_power_module::getMode() {
    return _mode;
}

float USB_C_power_module::getLimitA() {
    switch(_mode) {
        case Low_1000mA:
            return 1.0;
        case Medium_1500mA:
            return 1.5;
        case High_3000mA:
            return 3.0;
        default:
            _mode = Low_1000mA;
            return 1.0;
    }
}