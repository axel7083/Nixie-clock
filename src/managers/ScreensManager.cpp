//
// Created by axels on 17/02/2022.
//

#include "managers/ScreensManager.h"
#include "Clock.h"


void ScreensManager::begin(nullptr_t* config) {
    Serial.println("Booting screens");
    tfts.begin();
    updateClockDisplay(TFTs::force);
}

void ScreensManager::loop() {

    switch (state)
    {
        case State::OFF:
            if(tfts.isEnabled())
                tfts.disableAllDisplays();
            break;
        case State::CLOCK:
        case State::LOGS:
            if(!tfts.isEnabled())
                tfts.enableAllDisplays();
            break;
        case FIREWORKS:
            Clock::getInstance().animationsManager.loop();
            break;
    }

    if (state == State::CLOCK && millis() > timeForMore + 1000)
    {
        timeForMore = millis();
        updateClockDisplay(TFTs::yes);
    }

    #ifdef DEBUG
        debug();
    #endif
}

void ScreensManager::StartLogging() {
    state = State::LOGS;
    tfts.fillScreen(TFT_BLACK);
    tfts.setCursor(0, 0, 2);
    tfts.setTextSize(1);
}

void ScreensManager::logs(char *record, bool returnLine, uint16_t color, uint16_t background, bool force) {
    tfts.setTextColor(color, background);
    if(state == State::LOGS || force) {
        if(returnLine)
            tfts.println(record);
        else
            tfts.print(record);
    }
    else
        Serial.println("Error, trying to logs, when log mode is not activated.");
}

void ScreensManager::setBIGtext(char *text) {
    tfts.fillScreen(TFT_BLACK);
    tfts.setTextFont(LOAD_FONT8);
    tfts.setTextSize(10);
    for(int i = 0 ; i < 6 ; i ++) {
        tfts.chip_select.select(i);
        tfts.setCursor(30, 40, 2);
        tfts.print(text[i]);
    }
    tfts.setTextSize(1);
}

void ScreensManager::updateClockDisplay(TFTs::show_t show) {
    TimeManager time = Clock::getInstance().timeManager;

    tfts.setDigit(HOURS_TENS, time.getHours24Tens(), show);
    tfts.setDigit(HOURS_ONES, time.getHours24Ones(), show);
    tfts.setDigit(MINUTES_TENS, time.getMinutesTens(), show);
    tfts.setDigit(MINUTES_ONES, time.getMinutesOnes(), show);
    tfts.setDigit(SECONDS_TENS, time.getSecondsTens(), show);
    tfts.setDigit(SECONDS_ONES, time.getSecondsOnes(), show);
}

#ifdef DEBUG
void ScreensManager::debug() {
    tfts.chip_select.setHoursTens();
    tfts.setCursor(0, 0, 2);
    char buffer[100];
    sprintf(buffer, "Wifi Status: %d\nWifi SSID: ", Clock::getInstance().wifiManager.getStatus());
    logs(&buffer[0], false,TFT_WHITE,TFT_BLACK, true);
    logs(Clock::getInstance().wifiManager.getSavedSsid(), true,TFT_WHITE,TFT_BLACK, true);

    tfts.printf("Date: %d/%d/%d\n", Clock::getInstance().timeManager.getYear(), Clock::getInstance().timeManager.getMonth(), Clock::getInstance().timeManager.getDay());
}
#endif
void ScreensManager::setState(ScreensManager::State s) {
    // if the previous state was fireworks mode
    if(getState() == State::FIREWORKS) {
        Clock::getInstance().animationsManager.end();
    }

    switch (s) {
        case LOGS:
            break;
        case CLOCK:
            updateClockDisplay(TFTs::force);
            break;
        case FIREWORKS:
            Clock::getInstance().animationsManager.begin(&tfts);
            break;
        case OFF:
            break;
    }
    state = s;
}

