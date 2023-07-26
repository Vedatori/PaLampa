#ifndef _TOMAT_
#define _TOMAT_

#include <Arduino.h>
#include "Preferences.h"

#include <ESP32Ping.h>

#include "Illumination_module.h"
#include "WiFiCaptain.h"
#include <piezo/piezo.h>
#include <weather/weatherApi.h>
#include "USB_C_power_module.h"


namespace PL {

const int BUTTON_PIN[3] = {33, 25, 26};
const int BUZZER_PIN = 13;
const int BUZZER_CHANNEL = 3;
const int ONE_WIRE_BOTTOM_PIN = 15;
const int ONE_WIRE_TOP_PIN = 18;
const int LED_WARM_PIN = 5, LED_WARM_CHANNEL = 0;
const int LED_COLD_PIN = 17, LED_COLD_CHANNEL = 1;
const int LED_FREQ = 20000;
const int PHOTORES_UP_PIN = 34;
const int PHOTORES_BACK_PIN = 35;
const int LED_RGB_PIN = 16;
const int LED_RGB_COUNT = 16;

const char STORAGE_NAMESPACE[] = "PaLampa";
const uint16_t communicationTimeout = 1000;

const char WEATHER_API_KEY[] = "bde361c7c969906b9a9571a8f4a14c06";
const uint32_t INTERNET_UPDATE_PERIOD = 1000 * 60 * 15; // [ms]
const uint32_t SOFT_AP_DISABLE_TIMEOUT = 1000 * 60 * 5; // [ms]
const float idleCurrent = 0.1; // [A]

void refreshTaskQuick(void * param);
void refreshTaskSlow(void * param);
}

class PaLampa_class {
    bool beginCalled = false;
    bool connectionEnabled = false;
    bool connectionActive = false;
    uint32_t prevCommunicationTime = 0;
    bool internetConnected = false;
    bool wifiCaptStarted = false;

    float temperatureUp = 0.0;
    float temperatureDown = 0.0;

public:
    Illumination_module illumination;
    Piezo piezo;
	WeatherApi weather;
    USB_C_power_module power;
	
    void begin();
    bool buttonRead(int buttonID);
    void updateTemperature();
    float getTemperature();

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

extern PaLampa_class PaLampa;
extern Melody themeMelody;

#endif // _TOMAT_