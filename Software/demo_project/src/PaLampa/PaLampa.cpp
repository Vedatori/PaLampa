#include "PaLampa.h"

#include "SPIFFS.h"

Melody themeMelody(
	"TEMPO=150 " 
	"e4/4 e4/4 h3/4 e4/8 f#4/8 R/8 h3/8 R/2 g#4/8 R/4 R/16 e4/8 f#4/8 f#4/8 g#4/8 a4/4 e4/8 R/4 R/2 f#4/4 f#4/4 e4/4 d#4/8 e4/8 e4/8 f#4/8 R/4 R/8 e4/8 d#4/8 e4/8 e4/2 e4/2 e4/2"
);

void PL::refreshTaskQuick(void * parameter) {
    for(;;) {
        paLampa.oled.sendClear(true);
        paLampa.photoresistor.update();
        paLampa.lights.update();
        paLampa.capButton.update();
        
        delay(20);
    }
}

void PL::refreshTaskSlow(void * parameter) {
    for(;;) {
        paLampa.power.update();
        paLampa.thermometer.update();

        float lightCurrentLimit = paLampa.power.getLimitA() - PL::IDLE_CURRENT;
        if(paLampa.thermometer.get(1) == 0.0) {
            lightCurrentLimit = 0.9;
            printf("Error reading top light temperature. Limiting max current to default.\n");
        }
        else if(paLampa.thermometer.get(1) > PL::TEMP_LIMIT_TOP) {
            lightCurrentLimit = 0.0;
            printf("Maximum light temperature exceeded. Turning light off.\n");
        }
        else if(paLampa.thermometer.get(1) > PL::TEMP_LIMIT_BOTTOM) {
            float reductionRatio = (paLampa.thermometer.get(1) - PL::TEMP_LIMIT_BOTTOM) / (PL::TEMP_LIMIT_TOP - PL::TEMP_LIMIT_BOTTOM);
            lightCurrentLimit = lightCurrentLimit * (1 - reductionRatio);
            printf("Light temperature is getting too high. Reducing light current to %.2f A.\n", lightCurrentLimit);
        }
        paLampa.lights.setCurrentLimit(lightCurrentLimit);

        static uint32_t internetUpdateTime = 0;
        static uint32_t softApDisableTime = 0;
        static bool softApEnabled = true;
		if((millis() - internetUpdateTime) > PL::INTERNET_UPDATE_PERIOD || internetUpdateTime == 0) {
			paLampa.checkInternetConnected();
            if(paLampa.getInternetConnected()) {
                internetUpdateTime = millis();
                if(softApEnabled) {
                    softApDisableTime = millis();
                }
            }
            else if(paLampa.getWifiCaptStarted() && !softApEnabled) {
                softApEnable();
            }
		}
        if(paLampa.getInternetConnected()) {
            paLampa.weather.updateBothWF();
        }
        if(softApDisableTime != 0 && (millis() - softApDisableTime) > PL::SOFT_AP_DISABLE_TIMEOUT) {
            softApDisableTime = 0;
            softApEnabled = false;
            softApDisable();
        }
        delay(1000);
    }
}

void PaLampa::begin() {
    beginCalled = true;

    lights.begin();
    lights.setCurrentLimit(paLampa.power.getLimitA() - PL::IDLE_CURRENT);

	oled.begin();
    oled.drawLogo();
    oled.sendClear();
    
    capButton.begin();    
    capButton.setThreshold({5.0f, 2.0f});

    timeModule.begin();

    piezo.begin(PL::BUZZER_CHANNEL, PL::BUZZER_PIN);

    weather.init(1000 * 60 * 15);
    weather.setKey(PL::WEATHER_API_KEY, WEATHERAPI::WA_DEFAULT);
    weather.setPosition(50.36, 15.79, "Choteborky", WEATHERAPI::WA_DEFAULT);

    for(int i = 0; i < 3; ++i) {
        pinMode(PL::BUTTON_PIN[i], INPUT_PULLUP);
    }
    
    xTaskCreatePinnedToCore(PL::refreshTaskQuick, "refreshTaskQuick", 10000 , NULL, 3, NULL, 1);
    xTaskCreatePinnedToCore(PL::refreshTaskSlow, "refreshTaskSlow", 10000 , NULL, 0, NULL, 0);

    lights.setUpdateActive(true);
}

bool PaLampa::buttonRead(int buttonID) {
    if(buttonID < 0 || buttonID > 2) {
        printf("Invalid button ID: %d\n", buttonID);
        return 0;
    }
    return !digitalRead(PL::BUTTON_PIN[buttonID]);
}

float PaLampa::potentiometerRead() {
    return (4095 - analogRead(PL::POTENTIOMETER_PIN)) / 4095.0;
}

void PaLampa::printDiagnostics() {
    for(int i = 0; i <= 2; ++i) {
        printf("btn%d: %d ", i, buttonRead(i));
    }

    for(int i = 0; i < 2; i++){
        printf("CapBtn%d: %d ", i, capButton.getPadPressed(i));
    }

    printf("pot: %.2f ", potentiometerRead());
    
    printf(photoresistor.getText().c_str());

    //printf("priority: %d ", uxTaskPriorityGet(NULL));

    printf(thermometer.getText().c_str());

    printf("powerR: %.2f ", paLampa.lights.getCurrentLimitRatio());

    printf("time: %s ", timeModule.getClockText().c_str());

    printf("weather: %s \n", paLampa.weather.getWeather().getWeatherString().c_str());

}

void handleWeatherConfig(){
	String msg = "";
	if(webserver.hasArg("apiKey")){
		paLampa.weather.setKey(webserver.arg("apiKey"));
		msg = String("Api key set to: ") + paLampa.weather.getKey();
	}else if(webserver.hasArg("geoLocatorLatitude")){
		double latitude = webserver.arg("geoLocatorLatitude").toDouble();
		double longitude = webserver.arg("geoLocatorLongitude").toDouble();
		printf("%.10f %.10f",latitude, longitude);
		paLampa.weather.setPosition(latitude, longitude, "None");
		msg = String("Postion set to: ")+String(paLampa.weather.getPositionLatitude())+String(" ")+String(paLampa.weather.getPositionLongitude());
	}else{
		File f = SPIFFS.open("/weatherSetup.html", "r");
    	webserver.streamFile(f, "text/html");
		f.close();
		return;
	}
	String Page;
	Page += F("<html>\n\t<head>\n\t\t<meta charset=\"utf-8\">\n\t\t<meta name=\"viewport\" content=\"width=device-width, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0\">\n\t\t<meta name=\"theme-color\" content=\"#404040\"/>\n\t\t<title>TrackJet</title>\n\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n\t\t<style>\n\t\t\tbody {\n\t\t\t\toverflow : hidden;\n\t\t\t}\n\t\t\t</style>\n\t</head>\n\t<body>\n");
	Page += F("<p><a href='/'><input type = 'button' value = 'Remote Control page'/></a></p>");
	Page += msg;
	Page +=	F("</body></html>");

	webserver.send(200, "text/html", Page);
}

void PaLampa::startWiFiCaptain(String name, String password) {
    wifiCaptStarted = true;
    if(!beginCalled) {
        begin();
    }

    String ssid_final = "PaLampa-";
    if(name.isEmpty() || name == "<your_name>") {
        ssid_final += WiFi.macAddress();
    }
    else {
        ssid_final += name;
    }
    setApCredentials(ssid_final, password);
    wifiCaptInit();

	webserver.on("/weatherSetup", handleWeatherConfig);

    connectionEnabled = true;
}


bool PaLampa::getWifiCaptStarted() {
    return wifiCaptStarted;
}

void PaLampa::checkConnection() {
    if(!connectionEnabled) {
        return;
    }
    if(millis() > prevCommunicationTime + PL::communicationTimeout) {
        connectionActive = false;
    }
    else {
        connectionActive = true;
    }
}


void PaLampa::checkInternetConnected() {
	if(!WiFi.isConnected()) {
		internetConnected = false;
	}
    else {
        internetConnected = 
            Ping.ping(IPAddress(8, 8, 8, 8), 1) ||
            Ping.ping("google.com", 1) ||
            Ping.ping("vedatori.com", 1);
    }
}

bool PaLampa::getInternetConnected() {
    return internetConnected;
}

String PaLampa::commandGet() {
    String command = String(commandGetCaptain());
    command.toLowerCase();
    return command;
}

String PaLampa::commandGetIndexed(uint8_t index) {
    char commandBuffer[64];
    sprintf(commandBuffer, commandGetCaptain());
    const char delimiter[2] = " ";
    char *token;
    token = strtok((char *)commandBuffer, delimiter);
    for(uint8_t i = 0; i < index; ++i) {
        token = strtok(NULL, delimiter);
    }
    String command = String(token);
    command.toLowerCase();
    return command;
}

void PaLampa::commandClear() {
    commandClearCaptain();
}

void PaLampa::commandSend(String type, String text) {
    commandSendCaptain(type, text);
}

void PaLampa::commandDisp(String text) {
    commandSend("commandDisp", text);
}

PaLampa paLampa{};
