//
// Created by axels on 17/02/2022.
//

#include "managers/BackLightsManager.h"

void BackLightsManager::setPower(uint8_t value) {

    Serial.printf("Value %d\n", value);
    
    if(value == 0) {
        Serial.println("Set pattern dark");
        setPattern(BackLightsManager::Patterns::dark);
    }
    else {
        Serial.println("Set pattern rainbow");
        setPattern(BackLightsManager::Patterns::rainbow);
    }
    //TODO
}

uint16_t BackLightsManager::getPower() {
    return getPattern();
}

void BackLightsManager::setIntensity(uint8_t uint8) {
    Serial.println("[BackLightsManager] Set intensity");
    config->intensity = uint8;
}

uint8_t BackLightsManager::getIntensity() {
    return config->intensity;
}

void BackLightsManager::setPattern(uint8_t uint8) {
    this->setPattern(BackLightsManager::Patterns(uint8));
}

void BackLightsManager::setPattern(BackLightsManager::Patterns pattern) {
    this->config->pattern = pattern;
    pattern_needs_init = true;
}

uint8_t BackLightsManager::getPattern() {
    return config->pattern;
}

void BackLightsManager::setColor(uint8_t uint8) {
    //TODO
    pattern_needs_init = true;
}

uint32_t BackLightsManager::getColor() {
    return phaseToColor(config->color_phase);
}

void BackLightsManager::begin(Storage::Config::Backlights * config) {

    this->config = (Storage::Config::Backlights *) config;

    if (this->config->is_valid != Storage::valid) {
        Serial.println("Loaded Backlights config is invalid, using default.  This is normal on first boot.");
        setPattern(BackLightsManager::Patterns::rainbow);
        this->config->color_phase = 0;
        this->config->intensity = max_intensity-1;
        this->config->pulse_bpm = 72;
        this->config->breath_per_min = 10;
        this->config->is_valid = Storage::valid;
    }
}

void BackLightsManager::loop() {
    //   enum patterns { dark, test, constant, rainbow, pulse, breath, num_patterns };
    if (config->pattern == dark) {
        if (pattern_needs_init) {
            clear();
            show();
            pattern_needs_init = false;
        }
    }
    else if (config->pattern == constant) {
        if (pattern_needs_init) {
            setBrightness(0xFF >> (max_intensity - config->intensity - 1));
            fill(phaseToColor(config->color_phase));
            show();
            pattern_needs_init = false;
        }
    }
    else if (config->pattern == rainbow) {
        rainbowPattern();
    }
    else if (config->pattern == pulse) {
        pulsePattern();
    }
    else if (config->pattern == breath) {
        breathPattern();
    }
    
}

uint16_t BackLightsManager::getColorPhase() {
    return config->color_phase;
}

uint8_t BackLightsManager::phaseToIntensity(uint16_t phase) {
    uint16_t color;
    if (phase <= 255) {
        // Ramping up
        color = phase;
    } else if (phase <= 511) {
        // Ramping down
        color = 511 - phase;
    } else {
        // Off
        color = 0;
    }
    return uint8_t(color % 256);
}

uint32_t BackLightsManager::phaseToColor(uint16_t phase) {
    uint8_t red = phaseToIntensity(phase);
    uint8_t green = phaseToIntensity((phase + 256)%max_phase);
    uint8_t blue = phaseToIntensity((phase + 512)%max_phase);
    return(uint32_t(red) << 16 | uint32_t(green) << 8 | uint32_t(blue));
}

void BackLightsManager::rainbowPattern() {
    // Divide by 3 to spread it out some, so the whole rainbow isn't displayed at once.
    // TODO Make this /3 a parameter
    const uint16_t phase_per_digit = (max_phase/NUM_DIGITS)/3;

    // Divide by 10 to slow down the rainbow rotation rate.
    // TODO Make this /10 a parameter
    uint16_t phase = millis()/10 % max_phase;

    for (uint8_t digit=0; digit < NUM_DIGITS; digit++) {
        // Shift the phase for this LED.
        uint16_t my_phase = (phase + digit*phase_per_digit) % max_phase;
        setPixelColor(digit, phaseToColor(my_phase));
    }
    show();
}

void BackLightsManager::breathPattern() {
    if (pattern_needs_init) {
        fill(phaseToColor(config->color_phase));
        pattern_needs_init = false;
    }
    // https://sean.voisen.org/blog/2011/10/breathing-led-with-arduino/
    // Avoid a 0 value as it shuts off the LEDs and we have to re-initialize.
    float pulse_length_millis = (60.0f * 1000) / config->breath_per_min;
    float val = (exp(sin(2 * M_PI * millis() / pulse_length_millis)) - 0.36787944f) * 108.0f;

    uint8_t brightness = (uint8_t)val;
    if (brightness < 1) { brightness = 1; }
    setBrightness(brightness);
    show();
}

void BackLightsManager::pulsePattern() {
    if (pattern_needs_init) {
        fill(phaseToColor(config->color_phase));
        pattern_needs_init = false;
    }
    float pulse_length_millis = (60.0f * 1000) / config->breath_per_min;
    float val = 1 + abs(sin(2 * M_PI * millis() / pulse_length_millis)) * 254;
    setBrightness((uint8_t)val);
    show();
}

void BackLightsManager::toggle() {

    if(config->pattern != BackLightsManager::Patterns::dark)
        setPattern(BackLightsManager::Patterns::dark);
    else
    {
        setPattern(BackLightsManager::Patterns::rainbow);
    }
}
