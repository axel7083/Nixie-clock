//
// Created by axels on 17/02/2022.
//

#include "managers/ScreensManager.h"
#include "Clock.h"

void ScreensManager::begin(uint8_t* config) {
    Serial.println("Booting screens");
    tfts.begin();
    updateClockDisplay(TFTs::force);
}

void ScreensManager::loop() {
    if (state == State::CLOCK && millis() > timeForMore + 1000)
    {
        timeForMore = millis();
        updateClockDisplay(TFTs::yes);
    }
}

void ScreensManager::StartLogging() {
    state = State::LOGS;
    tfts.fillScreen(TFT_BLACK);
    tfts.setCursor(0, 0, 2);
    tfts.setTextSize(1);
}

void ScreensManager::logs(char *record, bool returnLine, uint16_t color, uint16_t background) {
    tfts.setTextColor(color, background);
    if(state == State::LOGS) {
        if(returnLine)
            tfts.println(record);
        else
            tfts.print(record);
    }
    else
        Serial.println("Error, trying to logs, when log mode is not activated.");
}

void ScreensManager::setBIGtext(char *text) {
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
