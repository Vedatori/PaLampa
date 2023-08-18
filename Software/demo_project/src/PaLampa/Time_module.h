/*
ONLINE RESOURCES:
Time zones: https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
"tm" structure: https://en.cppreference.com/w/c/chrono/tm
Custom time string formatting: https://cplusplus.com/reference/ctime/strftime/
"timeval" structure: https://man7.org/linux/man-pages/man2/settimeofday.2.html
*/

#ifndef _TIME_MODULE_
#define _TIME_MODULE_

#include "Arduino.h"
#include "time.h"

namespace time_module {
const char ntpServer1[] = "pool.ntp.org";
const char ntpServer2[] = "time.nist.gov";

/// Default time zone for Europe/Prague including daylight adjustment rules
/// Other time zones available at https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
const String defaultTimeZone = "CET-1CEST,M3.5.0,M10.5.0/3";

///Default SNTP sync interval in seconds
const int defaultSyncInterval = 5*60;

///SNTP status:
///OK - SNTP is running and last request was successful
///FAIL - SNTP is running and last request failed
///OFF - SNTP is disabled
enum sntpStatus {OK, FAIL, OFF};

}

class Time_module {
    bool beginCalled = false;
    int ntpSyncInterval;
    time_t ntpLastSync = -1;
public:
    // ========================= Configuration

    /// @brief Constructor using defaultSyncInterval as syncInterval
    Time_module();

    /// @brief Constructor with user set syncInterval
    /// @param syncInterval SNTP sync interval in seconds, min. 15 seconds
    Time_module(int syncInterval);

    /// @brief Initialization function, must be called before using any other methods
    /// @param sntpEnabled If set to false, SNTP will be disabled
    /// @param sntpTimeout SNTP sync timeout in seconds
    void begin(bool sntpEnabled = true, int sntpTimeout = -1);

    /// Enables/disables SNTP
    /// Begin must be called before using this function
    /// If you call setEnabled(true) and SNTP is already running, SNTP will be restarted.
    void setNtpEnabled(bool enabled);

    /// Returns true if SNTP is enabled, false otherwise
    bool isNtpEnabled();

    /// @brief Sets the timezone
    /// @param timeZone Timezone in posix timezone format
    void setTimeZone(String timeZone);

    /// @brief Sets time, use if SNTP fails or is disabled
    /// @param newTime timeval structure (seconds & microseconds)
    void setTime(struct timeval newTime);

    /// @brief Sets time, use if SNTP fails or is disabled
    /// @param newTime time.h tm structure
    void setTime(struct tm newTime);

    /// @brief Sets time, use if SNTP fails or is disabled, only sets hours and minutes
    void setTime(int hours, int minutes);

    /// @brief Shifts time by set ammount of minutes
    void shiftMinutes(int minutes);

    /// @brief Sets the SNTP sync interval
    /// @param syncInterval Seconds, min. 15 seconds
    void setSyncInterval(int syncInterval);



    // ========================= Reading configuration/status

    /// @brief Returns the SNTP sync interval
    /// @return Seconds
    int getSyncInterval();

    ///SNTP status:
    ///OK - SNTP is running and last request was successful
    ///FAILED - SNTP is running and last request failed
    ///STOP - SNTP is disabled
    time_module::sntpStatus getSntpStatus();

    /// @brief Returns the time of the last SNTP sync
    /// @return time_t
    time_t getLastSync();
    
    // ========================= Reading time

    /// @brief Returns current seconds since the epoch
    /// @return time_t (seconds)
    time_t getEpoch();

    /// @brief Returns current date-time 
    /// @return time.h tm structure
    struct tm getTime();

    /// @brief Returns current seconds and microseconds since the epoch
    /// @return timeval structure (seconds & microseconds)
    struct timeval getTimeval();

    /// @brief Returns clock text (e.g. 04:20, the leading 0 is intentional)
    /// @param colon Setting this to false will return clock text without a colon (e.g. 0420)
    String getClockText(bool colon = true);

    /// @brief Returns current date-time as string, terminated with \\n\0
    /// @return String
    String getTimeStr();
    /// @brief Returns current date-time as string with custom formatting
    /// @param format String format
    /// @return String
    String getTimeStr(const char* format);


    // ========================= Manipulating time representation

    /// @brief Converts tm struct to string, terminated with \\n\0
    /// @return String
    String tmToStr(struct tm time);
    /// @brief Converts tm struct to string with custom formatting
    /// @return String
    String tmToStr(struct tm time, const char* format);

    /// @brief Converts time_t to tm struct (UTC)
    /// @return time.h tm structure
    struct tm epochToUTC(time_t epoch);

    /// @brief Converts time_t to tm struct (local timezone)
    /// @return time.h tm structure
    struct tm epochToTm(time_t epoch);

    /// @brief Converts tm struct to time_t epoch (local timezone)
    /// @return time_t epoch
    time_t tmToEpoch(struct tm time);
};

#endif // _TIME_MODULE_