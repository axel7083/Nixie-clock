//
// Created by axels on 17/02/2022.
//

#include "managers/ButtonsManager.h"
#include "Clock.h"

void ButtonsManager::begin(uint8_t* config) {
    buttons.begin();
}

void ButtonsManager::loop() {
    buttons.loop();
    // Power
    switch (buttons.power.getState())
    {
        case Button::state::up_edge: // Button release
            // Toggle backlights
            Serial.println("Pressing power button");
            Clock::getInstance().backLightsManager.toggle();

            Clock::getInstance().screensManager.toggleScreens();

            break;
        case Button::state::up_long_edge: // Long press button release
            // Reboot
            //TODO
            ESP.restart();
            break;
        default:
            break;
    }

    // Mode
    switch (buttons.mode.getState())
    {
        case Button::state::up_edge: // Button release

            if(Clock::getInstance().screensManager.getState() == ScreensManager::State::FIREWORKS) {
                Clock::getInstance().screensManager.setState(ScreensManager::State::CLOCK);
            }
            else {
                Clock::getInstance().screensManager.setState(ScreensManager::State::FIREWORKS);
            }

            break;
        case Button::state::up_long_edge: // Long press button release

            break;
        default:
            break;
    }
}

