//
// Created by axels on 17/02/2022.
//

#include "managers/AlarmsManager.h"
#include "Clock.h"
#include <sstream>
#include <iomanip>

static Event defaultEvents[] = {
        {17,2, UINT16_MAX, "Axel's\nBirthday", 0},
        {17,6, UINT16_MAX, "Happy\nBirthday",0},
        {2, 8, 2022, "Axel\nDeparture",0},
        {1, 1, UINT16_MAX, "Happy\nnew year",0},
        {25, 12, UINT16_MAX, "Merry\nChristmas",0},
};

void AlarmsManager::begin(Storage::Config::Alarms* config) {
    // Invalid configuration (first boot)
    if(config->is_valid != Storage::valid) {
        Serial.println("[AlarmsManager] Invalid config: This is normal at first boot.");
        for(uint8_t i = 0 ; i < 5 ; i++) {
            defaultEvents[i].is_valid = Storage::valid;
            config->events[i] = defaultEvents[i];
        }
        config->is_valid = Storage::valid;
        Clock::getInstance().saveConfig();
    }

    this->config = config;
}

void AlarmsManager::loop() {
    // Refresh Every hour
    //if(millis() - refresh > 1000*60*60) {
       // Ensure a valid configuration
        if(config->is_valid != Storage::valid)
            return;

        // The day changed
        if(Clock::getInstance().timeManager.getDay() != current_day) {
            Serial.println("[AlarmsManager] day changed");
            update();
        }
    //}
}

void AlarmsManager::setAlarm(uint8_t index, uint8_t day, uint8_t month, uint16_t year, char *message) {
    if(index >= 5)
        return;

    config->events[index].day = day;
    config->events[index].month = month;
    config->events[index].year = year;
    config->events[index].day = day;
    strcpy(&(config->events[index].message)[0], message);
    config->events[index].is_valid = Storage::valid;

    Clock::getInstance().saveConfig();
    requireUpdate();
}

void AlarmsManager::resetAlarm() {

}

void AlarmsManager::update() {

    current_day = Clock::getInstance().timeManager.getDay();
    uint8_t current_month = Clock::getInstance().timeManager.getMonth();
    uint8_t current_year = Clock::getInstance().timeManager.getYear();

    bool has_event = false;

    for (Event item : config->events) {
        if(item.is_valid != Storage::valid) {
            Serial.println("[AlarmsManager] Event invalid.");
            continue;
        }

        if(item.day != current_day)
            continue;

        if(item.month != current_month)
            continue;

        if(item.year != UINT16_MAX && item.year != current_year)
            continue;

        setCurrentEvent(&item);
        has_event = true;
        break;
    }

    if(has_event)
        Clock::getInstance().screensManager.setState(ScreensManager::EVENT);
    else if(Clock::getInstance().screensManager.getState() != ScreensManager::OFF)
        Clock::getInstance().screensManager.setState(ScreensManager::CLOCK);
}

/**
 * This function return a stringify json array of
 * the events array stored.
 */
std::string AlarmsManager::getAlarms() {
    std::stringstream stringstream;
    stringstream << std::dec << std::setfill('0');

    stringstream << "[";
    bool hasPrevious = false;
    for(uint8_t i = 0; i < 5; i++) {
        if (config->events[i].is_valid != Storage::valid)
            continue;
        if(hasPrevious)
            stringstream << ",";

        stringstream << "{" <<
                     "\"i\":"<< (int)i <<
                     ",\"d\":"<< (int)config->events[i].day <<
                     ",\"m\":"<< (int)config->events[i].month <<
                     ",\"y\":"<< (int)config->events[i].year <<
                     ",\"t\":\""<< config->events[i].message << "\"}";

        hasPrevious = true;
    }

    stringstream << "]";

    return stringstream.str();
}

