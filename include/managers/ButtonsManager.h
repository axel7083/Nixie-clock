//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_BUTTONSMANAGER_H
#define CLOCK2_0_BUTTONSMANAGER_H
#include "Manager.h"
#include "models/Buttons.h"

class Managers;

class ButtonsManager: public Manager {
public:
    void loop() override;
    void begin(uint8_t* config) override;

private:
    Buttons buttons;
};


#endif //CLOCK2_0_BUTTONSMANAGER_H
