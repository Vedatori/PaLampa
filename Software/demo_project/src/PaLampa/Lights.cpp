#include "Lights.h"

ColorRGB red = {1, 0, 0};
ColorRGB green = {0, 1, 0};
ColorRGB blue = {0, 0, 1};
ColorRGB cyan = {0, 1, 1};
ColorRGB magenta = {1, 0, 1};
ColorRGB yellow = {1, 1, 0};
ColorRGB black = {0, 0, 0};
ColorRGB white = {1, 1, 1};
ColorRGB pink = {1, 0.75, 0.80};
ColorRGB brown = {0.65, 0.16, 0.16};
ColorRGB salmon = {0.98, 0.50, 0.45};
ColorRGB orange = {1, 0.65, 0};
ColorRGB gold = {1, 0.84, 0};

PanelSelector all = {1, 1};
PanelSelector top = {1, 0};
PanelSelector back = {0, 1};

ColorRGB dimColor(ColorRGB color, float brightness) {
    brightness = constrain(brightness, 0.0, 1.0);

    float * colorPtr = (float *)&color;
    for(int i = 0; i < 3; ++i) {
        colorPtr[i] = constrain(colorPtr[i] * brightness, 0, 1);
    }
    return color;
}

ColorRGB shiftColor(ColorRGB color, int red, int green, int blue) {
    color.red = constrain(color.red + red, 0, 1);
    color.green = constrain(color.green + green, 0, 1);
    color.blue = constrain(color.blue + blue, 0, 1);
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
    float X = C* (1- fabs(fmod(H / 60, 2)- 1));
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
    colorRGB.red = constrain(round((r+m)), 0, 1);
    colorRGB.green = constrain(round((g+m)), 0, 1);
    colorRGB.blue = constrain(round((b+m)), 0, 1);
    return colorRGB;
}

ColorHSV RGBtoHSV(ColorRGB color) {
    float * colorPtr = (float *)&color;
    float colorNorm[3];
    for(int colorID = 0; colorID < 3; ++colorID) {
        colorNorm[colorID] = constrain(colorPtr[colorID], 0, 1);
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

ColorRGB Lights::updateLedState(LedState& state, int timeStep) {
    ColorRGB targetColorDim = dimColor(state.targetColor, state.brightness);
    float * targetColorDimPtr = (float *)&targetColorDim;
    float * currentColorPtr = (float *)&state.currentColor;

    float deviation[3];
    for(int ledID = 0; ledID < 3; ++ledID) {
        deviation[ledID] = targetColorDimPtr[ledID] - currentColorPtr[ledID];
    }

    float step = 0;
    switch(state.transitionType) {
        case Linear: {
            step = timeStep / 1000.0 * 1.732 / state.transitionTime;
        } break;
        case Exponential: {
            float currentColorSize = pow(pow(currentColorPtr[0], 2) + pow(currentColorPtr[1], 2) + pow(currentColorPtr[2], 2), 0.5);
            float beginStep = 0.00006 * timeStep;
            step = beginStep + currentColorSize * (pow(1.732 / beginStep, timeStep / 1000.0 / state.transitionTime) - 1.0);
        } break;
        case None:
        default:
            step = 1.732;    // Maximal step to cover full diagonal at once
    }

    float devSize = pow(pow(deviation[0], 2) + pow(deviation[1], 2) + pow(deviation[2], 2), 0.5);
    float newColor[3];
    float * newColorPtr = (float *)&newColor;
    for(int ledID = 0; ledID < 3; ++ledID) {
        if(devSize < (step + PL::TRANS_END_THR)) {
            newColorPtr[ledID] = targetColorDimPtr[ledID];
        }
        else {
            newColorPtr[ledID] = currentColorPtr[ledID] + deviation[ledID] / devSize * step;
        }
    }
    state.updateNeeded = devSize > PL::TRANS_END_THR;

    for(int ledID = 0; ledID < 3; ++ledID) {
        currentColorPtr[ledID] = constrain(newColorPtr[ledID], 0, 1);
    }

    //printf("%.2f %.2f %.2f %.2f %.2f\n", deviation[0], devSize, step, currentColorPtr[0], state.currentColor.red);

    return state.currentColor;
}

Lights::Lights() :
    _ledColorState(std::vector<LedState>(PL::LED_RGB_COUNT)),
    _ledWhiteState(std::vector<float>(PL::LED_WHITE_COUNT)) {}

void Lights::begin() {
    pixels.begin();
    setColorPanels(all, black);
    setBrightness(all, 1.0);
    setTransition(all, None, 1.0);
    update();
    
    for(int ledID = 0; ledID < PL::LED_WHITE_COUNT; ++ledID) {
        ledcSetup(PL::LED_WHITE_CHANNEL[ledID], PL::LED_FREQ, PL::LED_RESOLUTION_BIT);
        ledcAttachPin(PL::LED_WHITE_PIN[ledID], PL::LED_WHITE_CHANNEL[ledID]);
    }
}

void Lights::update() {
    int timeNow = millis();
    static int timePrev = timeNow;
    int timeStep = timeNow - timePrev;
    timePrev = timeNow;

    if(_updateActive == false) {
        return;
    }

    bool updateNeeded = false;
    float sumColor = 0;
    for(uint8_t ledID = 0; ledID < PL::LED_RGB_COUNT; ++ledID) {
        ColorRGB currentColor = updateLedState(_ledColorState[ledID], timeStep);
        sumColor += (currentColor.red + currentColor.green + currentColor.blue);
        updateNeeded = updateNeeded || _ledColorState[ledID].updateNeeded;
    }
    if(sumColor <= 0) {
        sumColor = 0.001; // prevent zero division
    }

    float sumWhite = 0.0;
    for(int ledID = 0; ledID < PL::LED_WHITE_COUNT; ++ledID) {
        sumWhite += _ledWhiteState[ledID];
    }

    float currentTarget = sumColor * 0.012 + sumWhite * 1.5;
    float ratio = _currentLimit / currentTarget;
    _currentLimitRatio = constrain(ratio, 0.0, 1.0);

    for(uint8_t ledID = 0; ledID < PL::LED_RGB_COUNT; ++ledID) {
        ColorRGB powerLimitColor = dimColor(_ledColorState[ledID].currentColor, _currentLimitRatio);
        uint32_t color = pixels.Color(uint8_t(powerLimitColor.red * 255) , uint8_t(powerLimitColor.green * 255), uint8_t(powerLimitColor.blue * 255));
        pixels.setPixelColor(ledID, color);
    }

    for(int ledID = 0; ledID < PL::LED_WHITE_COUNT; ++ledID) {
        int powerLimitWhite = _ledWhiteState[ledID] * _currentLimitRatio * PL::LED_RESOLUTION_MAX_VAL;
        powerLimitWhite = constrain(powerLimitWhite, 0, PL::LED_RESOLUTION_MAX_VAL);
        ledcWrite(PL::LED_WHITE_CHANNEL[ledID], powerLimitWhite);
    }

    if(updateNeeded) {
        pixels.show();
    }
}

void Lights::setUpdateActive(bool state) {
    _updateActive = state;
}

void Lights::setCurrentLimit(float limit) {
    limit = constrain(limit, 0.0, 3.0);
    _currentLimit = limit;
}

float Lights::getCurrentLimitRatio() {
    return _currentLimitRatio;
}

void Lights::setWhite(int ledID, float brightness) {
    if(ledID < 0 || ledID >= PL::LED_WHITE_COUNT) {
        return;
    }
    brightness = constrain(brightness, 0.0, 1.0);
    _ledWhiteState[ledID] = brightness;
}

void Lights::setColor(int panelID, int ledID, ColorRGB color) {
    int ledAbsID = getLedAbsID(panelID, ledID);
    _ledColorState[ledAbsID].targetColor = color;
}

void Lights::setColor(int panelID, int ledID, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setColor(panelID, ledID, colorRGB);
}

void Lights::setColorPanel(int panelID, ColorRGB color) {
    int ledCount = 0;
    if(panelID == 0) {
        ledCount = 16;
    }
    else if(panelID == 1) {
        ledCount = 7;
    }
    else {
        return;
    }

    for(int i = 0; i < ledCount; ++i) {
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
            _ledColorState[ledID].brightness = brightness;
        }
    }
}

void Lights::setTransition(PanelSelector selector, TransitionType transition, float time) {
    if(time < PL::MIN_TRANS_T) {
        time = PL::MIN_TRANS_T;
    }

    for(int ledID = 0; ledID < PL::LED_RGB_COUNT; ++ledID) {
        int panelID = getPanelID(ledID);
        if(isPanelSelected(selector, panelID) == true) {
            _ledColorState[ledID].transitionType = transition;
            _ledColorState[ledID].transitionTime = time;
        }
    }
}