//
// Created by axels on 17/02/2022.
//

#include "managers/TimeManager.h"

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
    return RTC.get();
}
