#ifndef _LIGHTS_PL_H_
#define _LIGHTS_PL_H_

#include "Arduino.h"

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

class Lights_PL {
    static bool updateActive;                   // 0-not active, 1-active
public:
    static void begin();
    static void update();
    static void setUpdateActive(bool state);
    static void setCurrentLimit(float limit);
    static float getCurrentLimitRatio();
};

#endif // _LIGHTS_PL_H_