#include "Time_module.h"
#include "Preferences.h"
#include "esp_sntp.h"

Preferences timePreferences;
using namespace time_module;

Time_module::Time_module() {
    syncInterval = defaultSyncInterval;
}
Time_module::Time_module(int syncInterval) {
    this->syncInterval = syncInterval;
}

void Time_module::begin(int sntpTimeout) {
	timePreferences.begin("timeMod", false);
	setTimeZone(timePreferences.getString("timeZone", defaultTimeZone));
    timePreferences.end();

    if (syncInterval < 15) syncInterval = 15;

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

time_t Time_module::getEpoch() {
    return time(NULL);
}

struct tm Time_module::getTime() {
    time_t t;
    struct tm ttm;
    time(&t);
    localtime_r(&t, &ttm);
    return ttm;
}

timeval Time_module::getTimeval() {
    struct timeval tmp;
    gettimeofday(&tmp, NULL);
    return tmp;
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

String Time_module::getTimeStr() {
    time_t now;
    time(&now);
    char buffer[26];
    ctime_r(&now, buffer);
    return String(buffer);
}

String Time_module::getTimeStr(const char* format) {
    struct tm now = getTime();
    return Time_module::tmToStr(now, format);
}

String Time_module::tmToStr(struct tm time) {
    char buffer[26];
    asctime_r(&time, buffer);
    return String(buffer);
}

String Time_module::tmToStr(struct tm time, const char* format) {
    char buffer[128];
    size_t l = strftime(buffer, 128, format, &time);
    return String(buffer, (unsigned int)l);
}

struct tm Time_module::epochToUTC(time_t epoch) {
    struct tm ttm;
    gmtime_r(&epoch, &ttm);
    return ttm;
}

struct tm Time_module::epochToTm(time_t epoch) {
    struct tm ttm;
    localtime_r(&epoch, &ttm);
    return ttm;
}

time_t Time_module::tmToEpoch(struct tm time) {
    return mktime(&time);
}

double Time_module::diffTime(time_t end, time_t start) {
    return difftime(end, start);
}