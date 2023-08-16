#pragma once

#include <vector>
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

namespace PL {

const std::vector<int> LED_WHITE_PIN{5, 17};
const std::vector<int> LED_WHITE_CHANNEL{0, 11};
const int LED_WHITE_COUNT = 2;
const int LED_FREQ = 20000;
const int LED_RESOLUTION_BIT = 10;
const int LED_RESOLUTION_MAX_VAL = 1<<LED_RESOLUTION_BIT;

const int LED_RGB_PIN = 16;
const int LED_RGB_COUNT = 23;

const float MIN_TRANS_T = 0.1;
const float TRANS_END_THR = 1 / (LED_RESOLUTION_MAX_VAL + 1);
}

enum TransitionType {
    None = 0,
    Linear = 1,
    Exponential = 2
};

typedef struct colorRGB {
    float red;
    float green;
    float blue;
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

typedef struct ledColorState {
    ColorRGB targetColor;
    ColorRGB currentColor;
    float brightness;        // [0.0-1.0]
    TransitionType transitionType;
    float transitionTime;           // [seconds/fullRange]
    bool updateNeeded;
} LedColorState;

typedef struct ledWhiteState {
    float targetBrightness;        // [0.0-1.0]
    float currentBrightness;        // [0.0-1.0]
    TransitionType transitionType;
    float transitionTime;           // [seconds/fullRange]
    bool updateNeeded;
} LedWhiteState;

ColorRGB dimColor(ColorRGB color, float brightness);
ColorRGB shiftColor(ColorRGB color, float red, float green, float blue);
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
    std::vector<LedColorState> _ledColorState;
    std::vector<LedWhiteState> _ledWhiteState;
    bool _updateActive{};  // 0-not active, 1-active
    float _currentLimit{};                  // [A]
    float _currentLimitRatio{};

    bool isPanelSelected(PanelSelector selector, int panelID);
    int getPanelID(int ledID);
    int getLedAbsID(int panelID, int ledID);
    ColorRGB updateLedColorState(LedColorState& state, int timeStep);
    float updateLedWhiteState(LedWhiteState& state, int timeStep);

    Adafruit_NeoPixel pixels{PL::LED_RGB_COUNT, PL::LED_RGB_PIN, NEO_GRB + NEO_KHZ800};
public:
    Lights();
    void begin();
    void update();
    void setUpdateActive(bool state);
    void setCurrentLimit(float limit);
    float getCurrentLimitRatio();

    void setWhite(int ledID, float brightness);

    void setColor(int panelID, int ledID, ColorRGB color);
    void setColor(int panelID, int ledID, ColorHSV color);

    void setColorPanel(int panelID, ColorRGB color);
    void setColorPanel(int panelID, ColorHSV color);

    void setColorPanels(PanelSelector selector, ColorRGB color);
    void setColorPanels(PanelSelector selector, ColorHSV color);

    void setColorBrightness(PanelSelector selector, float brightness);

    void setWhiteTransition(std::vector<bool> selectLed, TransitionType aTransitionType, float time);
    void setColorTransition(PanelSelector selector, TransitionType aTransitionType, float time);
};
