#include "Lights.h"

ColorRGB red = {255, 0, 0};
ColorRGB green = {0, 255, 0};
ColorRGB blue = {0, 0, 255};
ColorRGB cyan = {0, 255, 255};
ColorRGB magenta = {255, 0, 255};
ColorRGB yellow = {255, 255, 0};
ColorRGB black = {0, 0, 0};
ColorRGB white = {255, 255, 255};
ColorRGB pink = {255, 192, 203};
ColorRGB brown = {165, 42, 42};
ColorRGB salmon = {250, 128, 114};
ColorRGB orange = {255, 165, 0};
ColorRGB gold = {255, 215, 0};
ColorRGB tomato = {255, 99, 71};

PanelSelector all = {1, 1};
PanelSelector top = {1, 0};
PanelSelector back = {0, 1};

ColorRGB dimColor(ColorRGB color, float brightness) {
    brightness = constrain(brightness, 0.0, 1.0);

    uint8_t * colorPtr = (uint8_t *)&color;
    for(int i = 0; i < 3; ++i) {
        colorPtr[i] = constrain(colorPtr[i] * brightness, 0, 255);
    }
    return color;
}

ColorRGB shiftColor(ColorRGB color, int red, int green, int blue) {
    color.red = constrain(color.red + red, 0, 255);
    color.green = constrain(color.green + green, 0, 255);
    color.blue = constrain(color.blue + blue, 0, 255);
    return color;
}

ColorRGB HSVtoRGB(ColorHSV color) {
    float H = color.hue;
    while(H < 0) {
        H += 360;
    }
    while(H > 360) {
        H -= 360;
    }
    float s = constrain(color.saturation, 0, 1);
    float v = constrain(color.value, 0, 1);

    float C = s*v;
    float X = C* (1- fabs(fmod(H/ 60, 2)- 1));
    float m = v-C;
    float r, g, b;

    if(H > 300) {
        r = C;
        g = 0;
        b = X;
    }
    else if(H > 240) {
        r = X;
        g = 0;
        b = C;
    }
    else if(H > 180) {
        r = 0;
        g = X;
        b = C;
    }
    else if(H > 120) {
        r = 0;
        g = C;
        b = X;
    }
    else if(H > 60) {
        r = X;
        g = C;
        b = 0;
    }
    else {
        r = C;
        g = X;
        b = 0;
    }
    
    ColorRGB colorRGB;
    colorRGB.red = constrain(round((r+m)*255), 0, 255);
    colorRGB.green = constrain(round((g+m)*255), 0, 255);
    colorRGB.blue = constrain(round((b+m)*255), 0, 255);
    return colorRGB;
}

ColorHSV RGBtoHSV(ColorRGB color) {
    uint8_t * colorPtr = (uint8_t *)&color;
    float colorNorm[3];
    for(int colorID = 0; colorID < 3; ++colorID) {
        colorNorm[colorID] = colorPtr[colorID] / 255.0;
    }

    int maxID = 0, minID = 0;  // 0-red, 1-green, 2-blue
    float mMax = 0, mMin = 0;
    if(colorNorm[0] >= colorNorm[1] && colorNorm[0] >= colorNorm[2]) {
        mMax = colorNorm[0];
        maxID = 0;
    }
    else if(colorNorm[1] >= colorNorm[0] && colorNorm[1] >= colorNorm[2]) {
        mMax = colorNorm[1];
        maxID = 1;
    }
    else {
        mMax = colorNorm[2];
        maxID = 2;
    }
    if(colorNorm[0] <= colorNorm[1] && colorNorm[0] <= colorNorm[2]) {
        mMin = colorNorm[0];
        minID = 0;
    }
    else if(colorNorm[1] <= colorNorm[0] && colorNorm[1] <= colorNorm[2]) {
        mMin = colorNorm[1];
        minID = 1;
    }
    else {
        mMin = colorNorm[2];
        minID = 2;
    }

    float c = mMax - mMin;
    float colorTemp[3];
    for(int colorID = 0; colorID < 3; ++colorID) {
        colorTemp[colorID] = (mMax - colorNorm[colorID]) / c;
    }
    float hTemp = 0;
    if(maxID == minID) {
        hTemp = 0;
    }
    else if (maxID == 0) {
        hTemp = colorTemp[2] - colorTemp[1];
    }
    else if (maxID == 1) {
        hTemp = 2 + colorTemp[0] - colorTemp[2];
    }
    else if (maxID == 2) {
        hTemp = 4 + colorTemp[1] - colorTemp[0];
    }
    while(hTemp < 0) {
        hTemp += 6.0;
    }
    while(hTemp > 6.0) {
        hTemp -= 6.0;
    }

    float hue = hTemp / 6 * 360;
    float saturation = c / mMax;
    float value = mMax;

    ColorHSV colorHSV;
    colorHSV.hue = constrain(hue, 0, 360);
    colorHSV.saturation = constrain(saturation, 0, 1);
    colorHSV.value = constrain(value, 0, 1);
    return colorHSV;
}

bool Lights::isPanelSelected(PanelSelector selector, int panelID) {
    switch(panelID) {
        case 0:
            return selector.top;
        case 1:
            return selector.back;
        default:
            return false;
    }
}

int Lights::getPanelID(int ledID) {
    if(ledID < 0)
        return -1;
    if(ledID < 16)
        return 0;
    if(ledID < 23)
        return 1;
    else
        return -1;
}

int Lights::getLedAbsID(int panelID, int ledID) {
    if(panelID < 0 || panelID > 1)
        return -1;
    if(ledID < 0 || ledID > 15)
        return -1;
    
    int ledAbsoluteID = 0;

    // Top LEDs
    if(panelID == 0)
        ledAbsoluteID = ledID;

    // Back LEDs
    else if(panelID == 1) {
        if(ledID > 6)
            return -1;
        ledAbsoluteID = 16 + ledID;
    }

    if(ledAbsoluteID < 0 || ledAbsoluteID > PL::LED_RGB_COUNT) {
        return -1;
    }
    return ledAbsoluteID;
}

ColorRGB Lights::updateLedState(LedState & state, int timeStep) {
    ColorRGB color = dimColor(state.targetColor, state.brightness);
    uint8_t * colorPtr = (uint8_t *)&color;
    
    float deviation[3];
    for(int ledID = 0; ledID < 3; ++ledID) {
        deviation[ledID] = colorPtr[ledID] - state.currentColorF[ledID];
    }

    float step = 0;
    switch(state.transitionType) {
        case Linear: {
            step = timeStep / 1000.0 * 441.7 / state.transitionTime;
        } break;
        case Exponential: {
            float currentColorSize = pow(pow(state.currentColorF[0], 2) + pow(state.currentColorF[1], 2) + pow(state.currentColorF[2], 2), 0.5);
            float beginStep = 0.015 * timeStep;
            step = beginStep + currentColorSize * (pow(441.7 / beginStep, timeStep / 1000.0 / state.transitionTime) - 1.0);
        } break;
        case None:
        default:
            step = 441.7;    // Maximal step to cover full diagonal at once
    }

    float devSize = pow(pow(deviation[0], 2) + pow(deviation[1], 2) + pow(deviation[2], 2), 0.5);
    for(int ledID = 0; ledID < 3; ++ledID) {
        if(devSize < (step + PL::TRANS_END_THR)) {
            state.currentColorF[ledID] = colorPtr[ledID];
        }
        else {
            state.currentColorF[ledID] += deviation[ledID] / devSize * step;
        }
    }
    state.updateNeeded = devSize > PL::TRANS_END_THR;
    
    state.currentColor.red = constrain(round(state.currentColorF[0]), 0, 255);
    state.currentColor.green = constrain(round(state.currentColorF[1]), 0, 255);
    state.currentColor.blue = constrain(round(state.currentColorF[2]), 0, 255);
    return state.currentColor;
}

Lights::Lights() :
    _ledState(std::vector<LedState>(PL::LED_RGB_COUNT)) {}

void Lights::begin() {
    pixels.begin();
    setColorPanels(all, black);
    setBrightness(all, 1.0);
    setTransition(all, None, 1.0);
    update();
    
    ledcSetup(PL::LED_WARM_CHANNEL, PL::LED_FREQ, PL::LED_RESOLUTION_BIT);
    ledcSetup(PL::LED_COLD_CHANNEL, PL::LED_FREQ, PL::LED_RESOLUTION_BIT);
    ledcAttachPin(PL::LED_WARM_PIN, PL::LED_WARM_CHANNEL);
    ledcAttachPin(PL::LED_COLD_PIN, PL::LED_COLD_CHANNEL);
}

void Lights::update() {
    int timeNow = millis();
    static int timePrev = timeNow;
    int timeStep = timeNow - timePrev;
    timePrev = timeNow;

    if(updateActive == false) {
        return;
    }

    bool updateNeeded = false;
    int sumRGB = 0;
    for(uint8_t ledID = 0; ledID < PL::LED_RGB_COUNT; ++ledID) {
        ColorRGB currentColor = updateLedState(_ledState[ledID], timeStep);
        sumRGB += (currentColor.red + currentColor.green + currentColor.blue);
        updateNeeded = updateNeeded || _ledState[ledID].updateNeeded;
    }

    if(sumRGB <= 0) {
        sumRGB = 1; // prevent zero division
    }
    float ratio = currentLimit / (float(sumRGB) / 255.0 / float(PL::LED_RGB_COUNT) * 1.12);
    currentLimitRatio = constrain(ratio, 0.0, 1.0);

    for(uint8_t ledID = 0; ledID < PL::LED_RGB_COUNT; ++ledID) {
        ColorRGB powerLimitColor = dimColor(_ledState[ledID].currentColor, currentLimitRatio);
        uint32_t color = pixels.Color(powerLimitColor.red, powerLimitColor.green, powerLimitColor.blue);
        pixels.setPixelColor(ledID, color);
    }

    if(updateNeeded) {
        pixels.show();
    }
}

void Lights::setUpdateActive(bool state) {
    updateActive = state;
}

void Lights::setCurrentLimit(float limit) {
    limit = constrain(limit, 0.0, 3.0);
    currentLimit = limit;
}

float Lights::getCurrentLimitRatio() {
    return currentLimitRatio;
}

void Lights::setWarm(float brightness) {
    int brightnessInt = brightness * PL::LED_RESOLUTION_MAX_VAL;
    brightnessInt = constrain(brightnessInt, 0, PL::LED_RESOLUTION_MAX_VAL);
    ledcWrite(PL::LED_WARM_CHANNEL, brightnessInt);
}

void Lights::setCold(float brightness) {
    int brightnessInt = brightness * PL::LED_RESOLUTION_MAX_VAL;
    brightnessInt = constrain(brightnessInt, 0, PL::LED_RESOLUTION_MAX_VAL);
    ledcWrite(PL::LED_COLD_CHANNEL, brightnessInt);
}

void Lights::setColor(int panelID, int ledID, ColorRGB color) {
    int ledAbsID = getLedAbsID(panelID, ledID);
    _ledState[ledAbsID].targetColor = color;
}

void Lights::setColor(int panelID, int ledID, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setColor(panelID, ledID, colorRGB);
}

void Lights::setColorPanel(int panelID, ColorRGB color) {
    for(int i = 0; i < 16; ++i) {
        setColor(panelID, i, color);
    }
}
void Lights::setColorPanel(int panelID, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setColorPanel(panelID, colorRGB);
}

void Lights::setColorPanels(PanelSelector selector, ColorRGB color) {
    for(int i = 0; i < 2; ++i) {
        if(isPanelSelected(selector, i) == true) {
            setColorPanel(i, color);
        }
    }
}

void Lights::setColorPanels(PanelSelector selector, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setColorPanels(selector, colorRGB);
}

void Lights::setBrightness(PanelSelector selector, float brightness) {
    brightness = constrain(brightness, 0.0, 1.0);

    for(int ledID = 0; ledID < PL::LED_RGB_COUNT; ++ledID) {
        int panelID = getPanelID(ledID);
        if(isPanelSelected(selector, panelID) == true) {
            _ledState[ledID].brightness = brightness;
        }
    }
}

void Lights::setTransition(PanelSelector selector, TransitionType transition, float rate) {
    if(rate < PL::MIN_TRANS_T) {
        rate = PL::MIN_TRANS_T;
    }

    for(int ledID = 0; ledID < PL::LED_RGB_COUNT; ++ledID) {
        int panelID = getPanelID(ledID);
        if(isPanelSelected(selector, panelID) == true) {
            _ledState[ledID].transitionType = transition;
            _ledState[ledID].transitionTime = rate;
        }
    }
}