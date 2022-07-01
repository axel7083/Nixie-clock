//
// Created by axels on 17/02/2022.
//

#include "managers/AlarmsManager.h"
#include "Clock.h"

static Birthday birthdays[] = {{17,2}, {17,6}, {2, 7}};

void AlarmsManager::begin(nullptr_t* config) { }

void AlarmsManager::loop() {
    // Refresh Every hour
    //if(millis() - refresh > 1000*60*60) {

        // The day changed
        if(Clock::getInstance().timeManager.getDay() != current_day) {
            Serial.println("[AlarmsManager] day changed");
            current_day = Clock::getInstance().timeManager.getDay();
            uint8_t current_month = Clock::getInstance().timeManager.getMonth();
            bool has_event = false;
            for (Birthday item : birthdays) {
                has_event |= item.day == current_day && item.month == current_month;
            }

            if(has_event)
                Clock::getInstance().screensManager.setState(ScreensManager::FIREWORKS);
            else if(Clock::getInstance().screensManager.getState() == ScreensManager::FIREWORKS)
                Clock::getInstance().screensManager.setState(ScreensManager::CLOCK);
        }
    //}
}

void AlarmsManager::setAlarm(uint8_t *uint8) {

}

void AlarmsManager::resetAlarm() {

}

