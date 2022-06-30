#ifndef UNIT_TEST

#include <Arduino.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <JPEGDecoder.h>
#include <DS1307RTC.h>

#include "Clock.h"

void setup() {
    Serial.begin(115200);
    Serial.println("[main] Clock begin");
    Clock::getInstance().begin();
}

void loop() {
    Clock::getInstance().loop();
}

#endif