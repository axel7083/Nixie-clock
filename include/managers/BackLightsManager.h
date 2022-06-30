//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_BACKLIGHTSMANAGER_H
#define CLOCK2_0_BACKLIGHTSMANAGER_H

#include "bluetooth/BacklightsService.h"
#include "Manager.h"
#include "utils/Storage.h"
#include "hardware/Hardware.h"
#include <Adafruit_NeoPixel.h>

class BackLightsManager: public Adafruit_NeoPixel, public BacklightsService, public Manager {
public:
    BackLightsManager(): Adafruit_NeoPixel(NUM_DIGITS, BACKLIGHTS_PIN, NEO_GRB + NEO_KHZ800), config(NULL),
        pattern_needs_init(true){}
    enum Patterns { dark, constant, rainbow, pulse, breath };

    void toggle();
    void setPower(uint8_t *uint8) override;
    uint16_t getPower() override;
    void setIntensity(uint8_t *uint8) override;
    uint8_t getIntensity() override;
    void setPattern(uint8_t *uint8) override;
    void setPattern(Patterns);
    uint8_t getPattern() override;
    void setColor(uint8_t *uint8) override;
    uint32_t getColor() override;


    uint16_t getColorPhase();

    void begin(uint8_t* config) override;
    void loop() override;
private:
    Storage::Config::Backlights *config;
    bool pattern_needs_init;
    void rainbowPattern();
    void pulsePattern();
    void breathPattern();

    // Helper methods
    uint8_t phaseToIntensity(uint16_t phase);
    uint32_t phaseToColor(uint16_t phase);

    const uint16_t max_phase = 768;   // 256 up, 256 down, 256 off
    const uint8_t max_intensity = 8;  // 0 to 7
    const uint32_t test_ms_delay = 250;
};


#endif //CLOCK2_0_BACKLIGHTSMANAGER_H
