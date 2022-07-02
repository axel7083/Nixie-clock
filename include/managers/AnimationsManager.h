//
// Created by axels on 01/07/2022.
//

#ifndef CLOCK2_0_ANIMATIONSMANAGER_H
#define CLOCK2_0_ANIMATIONSMANAGER_H

#include "Arduino.h"
#include "Manager.h"
#include "animation/firework.h"

class AnimationsManager: public Manager<TFTs> {
public:
    void loop() override;
    void begin(TFTs *config) override;
    void end() override;

    void createAnimators();

private:
    TFTs *tfts = nullptr;
    uint32_t millis_last_draw = 0;
    Animator *animators[6] = {};
};


#endif //CLOCK2_0_ANIMATIONSMANAGER_H
