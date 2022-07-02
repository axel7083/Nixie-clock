//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_ALARMSMANAGER_H
#define CLOCK2_0_ALARMSMANAGER_H
#include "Manager.h"
#include "models/Buttons.h"
#include "bluetooth/AlarmsService.h"
#include "utils/Storage.h"


class AlarmsManager: public AlarmsService, public Manager<Storage::Config::Alarms> {
public:
    void loop() override;
    void begin(Storage::Config::Alarms* config) override;
    void end() override {};

    void setAlarm(uint8_t *uint8) override;

    void resetAlarm() override;

    Event * getCurrentEvent() {
        return currentEvent;
    }

    void setCurrentEvent(Event * e) {
        currentEvent = e;
    }

private:
    unsigned long refresh = 0;
    uint8_t current_day = 0;
    Storage::Config::Alarms* config = nullptr;
    Event *currentEvent = nullptr;
};


#endif //CLOCK2_0_ALARMSMANAGER_H
