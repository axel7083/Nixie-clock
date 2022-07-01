//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_ALARMSMANAGER_H
#define CLOCK2_0_ALARMSMANAGER_H
#include "Manager.h"
#include "models/Buttons.h"
#include "bluetooth/AlarmsService.h"

class Managers;

class AlarmsManager: public AlarmsService, public Manager<nullptr_t> {
public:
    void loop() override;
    void begin(nullptr_t* config) override;

    void setAlarm(uint8_t *uint8) override;

    void resetAlarm() override;

private:

};


#endif //CLOCK2_0_ALARMSMANAGER_H
