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

Lights::Lights() {
    //pixels = Adafruit_NeoPixel(16, 16, NEO_GRB + NEO_KHZ800);
}

void Lights::begin() {
    /*pixels.begin();
    pixels.setPixelColor(0, pixels.Color(100, 0, 0));
    pixels.show();
    update();
    */
    ledcSetup(PL::LED_WARM_CHANNEL, PL::LED_FREQ, PL::LED_RESOLUTION_BIT);
    ledcSetup(PL::LED_COLD_CHANNEL, PL::LED_FREQ, PL::LED_RESOLUTION_BIT);
    ledcAttachPin(PL::LED_WARM_PIN, PL::LED_WARM_CHANNEL);
    ledcAttachPin(PL::LED_COLD_PIN, PL::LED_COLD_CHANNEL);
}

void Lights::update() {
    ;
}

void Lights::setUpdateActive(bool state) {
    ;
}

void Lights::setCurrentLimit(float limit) {
    ;
}

float Lights::getCurrentLimitRatio() {
    return 0.0;
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