#pragma once

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

}

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

class Lights {
    bool updateActive;  // 0-not active, 1-active

    //Adafruit_NeoPixel pixels;
public:
    Lights();
    void begin();
    void update();
    void setUpdateActive(bool state);
    void setCurrentLimit(float limit);
    float getCurrentLimitRatio();

    void setWarm(float brightness);
    void setCold(float brightness);
    void setColor(ColorRGB color);
    void setColor(ColorHSV color);
};
