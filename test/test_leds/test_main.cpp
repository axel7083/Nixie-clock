#include "Arduino.h"
#include "unity.h"
#include "Clock.h"

void test_power(void) {
    uint8_t power = 0;
    Clock::getInstance().backLightsManager.setPower(&power);
    TEST_ASSERT_EQUAL(Clock::getInstance().backLightsManager.getPower(), 0);
}

void test_pattern(void) {
    Clock::getInstance().backLightsManager.setPattern(BackLightsManager::Patterns::constant);
    TEST_ASSERT_EQUAL(Clock::getInstance().backLightsManager.getPattern(), BackLightsManager::Patterns::constant);
}

void setup() {
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);

    Serial.begin(115200);
    Serial.println("[main] Clock begin");
  
    Clock::getInstance().begin();
    Clock::getInstance().loop();

    UNITY_BEGIN();
    RUN_TEST(test_power);
    RUN_TEST(test_pattern);
    UNITY_END();
}

void loop() {}