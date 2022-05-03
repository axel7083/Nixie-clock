#ifndef CLOCK2_0_BUTTONS_H
#define CLOCK2_0_BUTTONS_H

/*
 * A simple helper class to call common functions on all buttons at once.
 */

#include "Button.h"
#include "hardware/Hardware.h"

class Buttons {
public:
    Buttons() : left(BUTTON_LEFT_PIN), mode(BUTTON_MODE_PIN), right(BUTTON_RIGHT_PIN), power(BUTTON_POWER_PIN) {}

    void begin()
    { left.begin(); mode.begin(); right.begin(); power.begin(); }
    void loop()
    { left.loop(); mode.loop(); right.loop(); power.loop(); }
    bool stateChanged()
    { return left.stateChanged() || mode.stateChanged() || right.stateChanged() || power.stateChanged(); }

    // Just making them public, so we don't have to proxy everything.
    Button left, mode, right, power;
private:
};


#endif //CLOCK2_0_BUTTONS_H
