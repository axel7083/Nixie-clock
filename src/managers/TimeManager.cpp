//
// Created by axels on 17/02/2022.
//

#include "managers/TimeManager.h"
#include "Clock.h"

void TimeManager::begin(Storage::Config::Clock* config) {
    this->config = config;

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

    // Every one hour seconds read rtc
    if(millis() - refresh_rtc > 1000*60*60) {
        setTime(syncProvider());
        refresh_rtc = millis();
    }
}

time_t TimeManager::syncProvider() {
    Serial.println("[Clock] syncProvider");
    time_t ntp_now, rtc_now;
    rtc_now = RTC.get();

    if(Clock::getInstance().wifiManager.getStatus() == WifiManager::Status::CONNECTED) {

        if(timeClient.update() || timeClient.forceUpdate()) {
            ntp_now = timeClient.getEpochTime();
            Serial.printf("[syncProvider] ntp_now %ld\n", ntp_now);

            // Check that the ntp_now look like something valid.
            if(year(ntp_now) < 2000) {
                Serial.printf("[syncProvider] Error ntp_now value\n");
                ESP.restart();
            }

            // Sync the RTC to NTP if needed.
            if (ntp_now != rtc_now) {
                RTC.set(ntp_now);
                rtc_now = ntp_now;
            }
        }
        else {
            Serial.printf("[syncProvider] timeClient update failed\n");
        }
    }

    return rtc_now;
}

WiFiUDP TimeManager::ntpUDP;
NTPClient TimeManager::timeClient(ntpUDP);

void TimeManager::setTimeZoneOffset(long offset) {
    config->time_zone_offset = offset;
    Clock::getInstance().saveConfig();
}
