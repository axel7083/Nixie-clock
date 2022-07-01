//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_BUTTONSMANAGER_H
#define CLOCK2_0_BUTTONSMANAGER_H
#include "Manager.h"
#include "models/Buttons.h"

class Managers;

class ButtonsManager: public Manager<nullptr_t> {
public:
    void loop() override;
    void begin(nullptr_t* config) override;
    void end() override {};

private:
    Buttons buttons;
};


#endif //CLOCK2_0_BUTTONSMANAGER_H
