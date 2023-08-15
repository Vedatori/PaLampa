#pragma once

#include <Arduino.h>
#include "Preferences.h"

#include <ESP32Ping.h>

#include "Photoresistor.h"
#include "Thermometer.h"
#include "Lights.h"
#include "WiFiCaptain.h"
#include <piezo/piezo.h>
#include <weather/weatherApi.h>
#include "USB_C_power_module.h"


namespace PL {

const int BUTTON_PIN[3] = {33, 25, 26};
const int POTENTIOMETER_PIN = 36;
const int PHOTORESISTOR_TOP_PIN = 34;
const int PHOTORESISTOR_BACK_PIN = 35;
const int THERMOMETER_BOTTOM_PIN = 15;
const int THERMOMETER_TOP_PIN = 18;
const int BUZZER_PIN = 13, BUZZER_CHANNEL = 3;

const char STORAGE_NAMESPACE[] = "PaLampa";
const uint16_t communicationTimeout = 1000;

const char WEATHER_API_KEY[] = "bde361c7c969906b9a9571a8f4a14c06";
const uint32_t INTERNET_UPDATE_PERIOD = 1000 * 60 * 15; // [ms]
const uint32_t SOFT_AP_DISABLE_TIMEOUT = 1000 * 60 * 5; // [ms]
const float IDLE_CURRENT = 0.1; // [A]

void refreshTaskQuick(void * param);
void refreshTaskSlow(void * param);

}

class PaLampa {
    bool beginCalled = false;
    bool connectionEnabled = false;
    bool connectionActive = false;
    uint32_t prevCommunicationTime = 0;
    bool internetConnected = false;
    bool wifiCaptStarted = false;

    float temperatureUp = 0.0;
    float temperatureDown = 0.0;

public:
    Photoresistor photoresistor{{PL::PHOTORESISTOR_TOP_PIN, PL::PHOTORESISTOR_BACK_PIN}};
    Thermometer thermometer{{PL::THERMOMETER_BOTTOM_PIN, PL::THERMOMETER_TOP_PIN}};
    Lights lights{};
    Piezo piezo;
	WeatherApi weather;
    USB_C_power_module power;
	
    void begin();
    bool buttonRead(int buttonID);
    float potentiometerRead();


    void printDiagnostics();

    void startWiFiCaptain(String name="", String password="");
    bool getWifiCaptStarted();
    void checkConnection();
    void checkInternetConnected();
	bool getInternetConnected();
    String commandGet();
    String commandGetIndexed(uint8_t index);
    void commandClear();
    void commandSend(String type, String text);
    void commandDisp(String text);
};

extern PaLampa paLampa;
extern Melody themeMelody;
