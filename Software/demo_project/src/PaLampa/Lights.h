#pragma once

#include <vector>
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

namespace PL {

const int LED_WARM_PIN = 5, LED_WARM_CHANNEL = 0;
const int LED_COLD_PIN = 17, LED_COLD_CHANNEL = 1;
const int LED_FREQ = 20000;
const int LED_RESOLUTION_BIT = 10;
const int LED_RESOLUTION_MAX_VAL = 1<<LED_RESOLUTION_BIT;
const int LED_RGB_PIN = 16;
const int LED_RGB_COUNT = 23;

const float MIN_TRANS_T = 0.1;
const float TRANS_END_THR = 0.1;
}

enum TransitionType {
    None = 0,
    Linear = 1,
    Exponential = 2
};

typedef struct colorRGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} ColorRGB;

typedef struct colorHSV {
    float hue;
    float saturation;
    float value;
} ColorHSV;

typedef struct panelSelector {
    bool top;
    bool back;
} PanelSelector;

typedef struct ledState {
    ColorRGB targetColor;
    ColorRGB currentColor;
    float currentColorF[3];          // {red, green, blue} - True displayed color
    float brightness;           // [0.0-1.0]
    TransitionType transitionType;
    float transitionTime;           // [seconds/fullRange]
    bool updateNeeded;
} LedState;

ColorRGB dimColor(ColorRGB color, float brightness);
ColorRGB shiftColor(ColorRGB color, int red, int green, int blue);
ColorRGB HSVtoRGB(ColorHSV color);
ColorHSV RGBtoHSV(ColorRGB color);

extern ColorRGB red;
extern ColorRGB green;
extern ColorRGB blue;
extern ColorRGB cyan;
extern ColorRGB magenta;
extern ColorRGB yellow;
extern ColorRGB black;
extern ColorRGB white;
extern ColorRGB pink;
extern ColorRGB brown;
extern ColorRGB salmon;
extern ColorRGB orange;
extern ColorRGB gold;
extern ColorRGB tomato;

extern PanelSelector all;
extern PanelSelector top;
extern PanelSelector back;

class Lights {
    std::vector<LedState> _ledState;
    bool updateActive{};  // 0-not active, 1-active
    float currentLimit{};                  // [A]
    float currentLimitRatio{};

    bool isPanelSelected(PanelSelector selector, int panelID);
    int getPanelID(int ledID);
    int getLedAbsID(int panelID, int ledID);
    ColorRGB updateLedState(LedState & state, int timeStep);

    Adafruit_NeoPixel pixels{PL::LED_RGB_COUNT, PL::LED_RGB_PIN, NEO_GRB + NEO_KHZ800};
public:
    Lights();
    void begin();
    void update();
    void setUpdateActive(bool state);
    void setCurrentLimit(float limit);
    float getCurrentLimitRatio();

    void setWarm(float brightness);
    void setCold(float brightness);

    void setColor(int panelID, int ledID, ColorRGB color);
    void setColor(int panelID, int ledID, ColorHSV color);

    void setColorPanel(int panelID, ColorRGB color);
    void setColorPanel(int panelID, ColorHSV color);

    void setColorPanels(PanelSelector selector, ColorRGB color);
    void setColorPanels(PanelSelector selector, ColorHSV color);

    void setBrightness(PanelSelector selector, float brightness);
    void setTransition(PanelSelector selector, TransitionType aTransitionType, float apanelTransRate);
};
