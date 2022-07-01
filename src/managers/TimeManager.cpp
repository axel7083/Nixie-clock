//
// Created by axels on 17/02/2022.
//

#include "managers/TimeManager.h"
#include "Clock.h"

void TimeManager::begin(uint8_t* config) {
    this->config = (Storage::Config::Clock*) config;

    if (this->config->is_valid != Storage::valid) {
        // Config is invalid, probably a new device never had its config written.
        // Load some reasonable defaults.
        Serial.println("Loaded Clock config is invalid, using default.  This is normal on first boot.");
        setTwelveHour(false);
        setTimeZoneOffset(0);
        this->config->is_valid = Storage::valid;
    }

    //RTC.set(RTC.get() + 60*60);
    setSyncProvider(&TimeManager::syncProvider);
}

void TimeManager::loop() {
    if (timeStatus() == timeNotSet) {
        time_valid = false;
    }
    else {
        loop_time = now();
        local_time = loop_time + config->time_zone_offset;
        time_valid = true;
    }

    // Every 100 seconds read rtc
    if(millis() - refresh_rtc > 100000) {
        setTime(syncProvider());
        refresh_rtc = millis();
    }
}

time_t TimeManager::syncProvider() {
    Serial.println("[Clock] syncProvider");
    time_t ntp_now, rtc_now;
    rtc_now = RTC.get();

    if(Clock::getInstance().wifiManager.getStatus() == WifiManager::Status::CONNECTED) {
        timeClient.update();
        ntp_now = timeClient.getEpochTime();

        // Sync the RTC to NTP if needed.
        if (ntp_now != rtc_now) {
            RTC.set(ntp_now);
            rtc_now = ntp_now;
        }
    }

    return rtc_now;
}

WiFiUDP TimeManager::ntpUDP;
NTPClient TimeManager::timeClient(ntpUDP);
