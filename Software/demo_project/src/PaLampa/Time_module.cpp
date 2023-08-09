#include "Time_module.h"
#include "Preferences.h"
#include "esp_sntp.h"

Preferences timePreferences;
using namespace time_module;

Time_module::Time_module(){
    syncInterval = defaultSyncInterval;
}
Time_module::Time_module(int syncInterval){
    this->syncInterval = syncInterval;
}


void Time_module::begin(int sntpTimeout) {
	timePreferences.begin("timeMod", false);
	setTimeZone(timePreferences.getString("timeZone", defaultTimeZone));
    timePreferences.end();

    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    sntp_set_sync_interval(syncInterval);
    sntp_setservername(1, ntpServer1);
    sntp_setservername(2, ntpServer2);
    sntp_init();

    
    if(sntpTimeout>0){
        int sntpTimeoutMs = sntpTimeout*1000;
        uint32_t start = millis();
        bool syncFailed = true;
        while((millis()-start) <= sntpTimeoutMs) {
            sntp_sync_status_t syncStatus = sntp_get_sync_status();
            if(syncStatus == SNTP_SYNC_STATUS_COMPLETED){
                syncFailed = false;
                break;
            }
            vTaskDelay(1);
        }
        if(syncFailed){
            printf("Failed to synchronize SNTP within %d seconds\n", sntpTimeout);
        }
    }
}

void Time_module::setTimeZone(String newTimeZone) {
	setenv("TZ", newTimeZone.c_str(), 1);
	tzset();

    timePreferences.begin("timeMod", false);
	timePreferences.putString("timeZone", newTimeZone);
    timePreferences.end();
}


struct tm Time_module::getTime() {
    time_t t;
    time(&t);
    return *localtime(&t);
}

String Time_module::getClockText(bool colon) {
    char clockText[6];
    struct tm now = getTime();
    if(colon){
        sprintf(clockText, "%02d:%02d", now.tm_hour, now.tm_min);
    }else{
        sprintf(clockText, "%02d%02d", now.tm_hour, now.tm_min);
    }
    return String(clockText);
}
