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

///Default SNTP sync interval in ms
const int defaultSyncInterval = 5*60*1000;
}


class Time_module {
    int syncInterval;
public:
    /// @brief Constructor using defaultSyncInterval as syncInterval
    Time_module();

    /// @brief Constructor with user set syncInterval
    /// @param syncInterval SNTP sync interval in milliseconds
    Time_module(int syncInterval);

    /// @brief Initialization function, must be called before using any other methods
    /// @param sntpTimeout SNTP sync timeout in seconds
    void begin(int sntpTimeout = -1);

    /// @brief Sets the timezone
    /// @param timeZone Timezone in posix timezone format
    void setTimeZone(String timeZone);

    /// @brief Returns current time
    /// @return time.h tm structure https://en.cppreference.com/w/c/chrono/tm
    struct tm getTime();

    /// @brief Returns clock text (e.g. 04:20, the leading 0 is intentional)
    /// @param colon Setting this to false will return clock text without a colon (e.g. 0420)
    String getClockText(bool colon = true);
};

#endif // _TIME_MODULE_