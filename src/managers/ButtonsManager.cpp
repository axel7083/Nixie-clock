//
// Created by axels on 17/02/2022.
//

#include "managers/ButtonsManager.h"
#include "Clock.h"

void ButtonsManager::begin(nullptr_t* config) {
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

            // We use the backlights as a reference to force sync the backlights state and the screens state
            if(Clock::getInstance().backLightsManager.getPattern() == BackLightsManager::Patterns::dark) {
                Clock::getInstance().backLightsManager.setPattern(BackLightsManager::Patterns::rainbow);
                Clock::getInstance().screensManager.setState(ScreensManager::CLOCK);
            }
            else {
                Clock::getInstance().backLightsManager.setPattern(BackLightsManager::Patterns::dark);
                Clock::getInstance().screensManager.setState(ScreensManager::OFF);
            }

            break;
        case Button::state::up_long_edge: // Long press button release
            // Reboot
            //TODO
            Clock::getInstance().saveConfig();
            ESP.restart();
            break;
        default:
            break;
    }
    uint8_t s = Clock::getInstance().screensManager.getState();
    // Mode
    switch (buttons.mode.getState())
    {
        case Button::state::up_edge: // Button release
            /*if(s == ScreensManager::State::EVENT) {
                Clock::getInstance().screensManager.setState(ScreensManager::State::CLOCK);
            }
            else {
                Clock::getInstance().screensManager.setState(ScreensManager::State::FIREWORKS);
            }*/
            break;
        case Button::state::up_long_edge: // Long press button release

            break;
        default:
            break;
    }
}

