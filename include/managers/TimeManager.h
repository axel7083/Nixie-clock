//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_TIMEMANAGER_H
#define CLOCK2_0_TIMEMANAGER_H
#include "Manager.h"
#include <stdint.h>
#include <TimeLib.h>

// For NTP
#include <WiFi.h>
#include <NTPClient.h>

// For the DS3231 RTC
#include <DS1307RTC.h>

#include "utils/Storage.h"
#include "hardware/TFTs.h"
#include "bluetooth/TimeService.h"

class TimeManager: public Manager<Storage::Config::Clock>, public TimeService {
public:
    TimeManager(): loop_time(0), local_time(0), time_valid(false), config(NULL) {}
    void loop() override;
    void begin(Storage::Config::Clock* config) override;
    void end() override {};

    // Calls NTPClient::getEpochTime() or RTC::get() as appropriate
    // This has to be static to pass to TimeLib::setSyncProvider.
    static time_t syncProvider();

    // Set preferred hour format. true = 12hr, false = 24hr
    void setTwelveHour(bool th)           { config->twelve_hour = th; }
    bool getTwelveHour()                  { return config->twelve_hour; }
    void toggleTwelveHour()               { config->twelve_hour = !config->twelve_hour; }

    // Internal time is kept in UTC. This affects the displayed time.
    void setTimeZoneOffset(long offset) override ;
    time_t getTimeZoneOffset()            { return config->time_zone_offset; }
    void adjustTimeZoneOffset(time_t adj) { config->time_zone_offset += adj; }

    // Proxy C functions from TimeLib.h
    // I really wish it were a class we could just subclass, but here we are.
    uint16_t getYear()       { return year(local_time); }
    uint8_t getMonth()       { return month(local_time); }
    uint8_t getDay()         { return day(local_time); }
    uint8_t getHour()        { return config->twelve_hour ? hourFormat12(local_time) : hour(local_time); }
    uint8_t getHour12()      { return hourFormat12(local_time); }
    uint8_t getHour24()      { return hour(local_time); }
    uint8_t getMinute()      { return minute(local_time); }
    uint8_t getSecond()      { return second(local_time); }
    bool isAm()              { return isAM(local_time); }
    bool isPm()              { return isPM(local_time); }

    // Helper functions for making a clock.
    uint8_t getHoursTens()    { return getHour()/10;   }
    uint8_t getHoursOnes()    { return getHour()%10;   }
    uint8_t getHours12Tens()  { return getHour12()/10; }
    uint8_t getHours12Ones()  { return getHour12()%10; }
    uint8_t getHours24Tens()  { return getHour24()/10; }
    uint8_t getHours24Ones()  { return getHour24()%10; }
    uint8_t getMinutesTens()  { return getMinute()/10; }
    uint8_t getMinutesOnes()  { return getMinute()%10; }
    uint8_t getSecondsTens()  { return getSecond()/10; }
    uint8_t getSecondsOnes()  { return getSecond()%10; }

private:
    time_t loop_time, local_time;
    bool time_valid;
    Storage::Config::Clock *config;

    // Static variables needed for syncProvider()
    static WiFiUDP ntpUDP;
    static NTPClient timeClient;
    //static NTPClient ntpTimeClient;
    //static uint32_t millis_last_ntp;
    //const static uint32_t refresh_ntp_every_ms = 3600000; // Get new NTP every hour, use RTC in between.
    unsigned long refresh_rtc = 0;
};


#endif //CLOCK2_0_TIMEMANAGER_H
