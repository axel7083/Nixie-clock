//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_SCREENSMANAGER_H
#define CLOCK2_0_SCREENSMANAGER_H
#include "Manager.h"
#include "hardware/TFTs.h"
#include "utils/Storage.h"
#include "TimeManager.h"


class ScreensManager: public Manager<nullptr_t> {
public:
    enum State {
        LOGS = 0,
        CLOCK = 1,
        FIREWORKS = 2,
        OFF,
    };

    void toggleScreens() { if(state == State::OFF) state = State::CLOCK; else state = State::OFF; };
    void begin(nullptr_t* config) override;
    void loop() override;
    void end() override {};

    void StartLogging();
    void logs(char *, bool returnLine = true, uint16_t color = TFT_WHITE, uint16_t background = TFT_BLACK, bool force = false);
    void debug();
    void setBIGtext(char text[]);

    State getState() {
        return state;
    }

    void setState(State s);


private:
    TFTs tfts;    // Display module driver
    void updateClockDisplay(TFTs::show_t show);
    u_long timeForMore = millis();
    State state = State::LOGS;


};


#endif //CLOCK2_0_SCREENSMANAGER_H
