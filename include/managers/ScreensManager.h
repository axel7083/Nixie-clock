//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_SCREENSMANAGER_H
#define CLOCK2_0_SCREENSMANAGER_H
#include "Manager.h"
#include "hardware/TFTs.h"
#include "utils/Storage.h"
#include "TimeManager.h"

class ScreensManager: public Manager {
public:
    enum State {
        LOGS = 0,
        CLOCK = 1
    };
    State state = State::LOGS;

    void begin(uint8_t* config) override;
    void loop() override;

    void StartLogging();
    void logs(char *, bool returnLine = true, uint16_t color = TFT_WHITE, uint16_t background = TFT_BLACK);

    void setBIGtext(char text[]);
private:
    TFTs tfts;    // Display module driver
    void updateClockDisplay(TFTs::show_t show);
    u_long timeForMore = millis();

};


#endif //CLOCK2_0_SCREENSMANAGER_H
