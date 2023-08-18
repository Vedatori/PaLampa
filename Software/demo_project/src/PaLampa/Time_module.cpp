#include "Time_module.h"
#include "Preferences.h"
#include "esp_sntp.h"

Preferences timePreferences;
using namespace time_module;

Time_module::Time_module() {
    ntpSyncInterval = defaultSyncInterval;
}
Time_module::Time_module(int syncInterval) {
    this->ntpSyncInterval = syncInterval;
}

void Time_module::begin(bool sntpEnabled, int sntpTimeout) {
    //Begin already called check
    if (beginCalled) {
        printf("TimeModule: Begin already called, aborting!\n"); 
        return; 
    } 
    beginCalled = true;
    
    //Load timezone
	timePreferences.begin("timeMod", false);
	setTimeZone(timePreferences.getString("timeZone", defaultTimeZone));
    timePreferences.end();

    //Invalid sync interval check
    if (ntpSyncInterval < 15) ntpSyncInterval = 15;

    //Config sntp
    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    sntp_set_sync_interval(ntpSyncInterval*1000);
    sntp_setservername(1, ntpServer1);
    sntp_setservername(2, ntpServer2);

    //Init sntp
    if(sntpEnabled){
        sntp_init();
        
        //Wait for first sync
        if(sntpTimeout>0){
            int sntpTimeoutMs = sntpTimeout*1000;
            uint32_t start = millis();
            bool syncFailed = true;
            while((millis()-start) <= sntpTimeoutMs) {
                if(getSntpStatus() == sntpStatus::OK){
                    syncFailed = false;
                    break;
                }
                vTaskDelay((int)(200/portTICK_PERIOD_MS));
            }
            if(syncFailed){
                printf("Failed to synchronize SNTP within %d seconds\n", sntpTimeout);
            }
        }
    }
}

void Time_module::setNtpEnabled(bool enabled) {
    if(!beginCalled){
        printf("TimeModule: Can't call setEnabled without calling begin first!\n");
        return;
    }
    if(enabled){
        if(sntp_enabled()){
            sntp_restart();
        }else{
            sntp_init();
        }
    }else{
        if(sntp_enabled()){
            sntp_stop();
        }
    }
}

bool Time_module::isNtpEnabled() {
    return sntp_enabled();
}

void Time_module::setTimeZone(String newTimeZone) {
	setenv("TZ", newTimeZone.c_str(), 1);
	tzset();

    timePreferences.begin("timeMod", false);
	timePreferences.putString("timeZone", newTimeZone);
    timePreferences.end();
}

void Time_module::setTime(struct timeval newTime) {
    setNtpEnabled(false);
    settimeofday(&newTime, NULL);
}

void Time_module::setTime(struct tm newTime) {
    setTime((struct timeval){tmToEpoch(newTime), 0});
}

void Time_module::setTime(int hours, int minutes) {
    struct tm t = getTime();
    t.tm_hour = hours;
    t.tm_min = minutes;
    setTime(t);
}

void Time_module::shiftMinutes(int minutes) {
    time_t t = time(NULL);
    t = t + minutes*60;
    setTime(epochToTm(t));
}

void Time_module::setSyncInterval(int syncInterval) {
    if (syncInterval < 15) syncInterval = 15;
    ntpSyncInterval = syncInterval;
    sntp_set_sync_interval(ntpSyncInterval*1000);
    if(sntp_enabled()){
        sntp_restart();
    }
}

int Time_module::getSyncInterval() {
    return sntp_get_sync_interval()/1000;
}

sntpStatus Time_module::getSntpStatus() {
    if(!sntp_enabled()) return sntpStatus::OFF;

    sntp_sync_status_t syncStatus = sntp_get_sync_status();
    if(syncStatus == SNTP_SYNC_STATUS_COMPLETED){
        //printf("NTP Synced!");
        ntpLastSync = time(NULL);
        return sntpStatus::OK;
    }

    if(ntpLastSync == -1) return sntpStatus::FAIL;

    if( (time(NULL)-ntpLastSync) < (ntpSyncInterval+15) ) {
        return sntpStatus::OK;
    }else{
        return sntpStatus::FAIL;
    }
}

time_t Time_module::getLastSync() {
    return ntpLastSync;
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
