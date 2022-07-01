//
// Created by axels on 01/07/2022.
//

#ifndef CLOCK2_0_ANIMATIONSMANAGER_H
#define CLOCK2_0_ANIMATIONSMANAGER_H

#include "Arduino.h"
#include "Manager.h"
#include "animation/firework.h"

class AnimationsManager: public Manager {
public:
    void loop() override;
    void begin(uint8_t *config) override;
    void end() override;

private:
    TFTs *tfts = nullptr;
    uint32_t millis_last_draw;
    Animator *animators[6];
};


#endif //CLOCK2_0_ANIMATIONSMANAGER_H
