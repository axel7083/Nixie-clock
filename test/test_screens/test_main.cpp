#include "Arduino.h"
#include "unity.h"

void test_example(void) {
  TEST_ASSERT_EQUAL(0, 0);
}

void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  UNITY_BEGIN();
  RUN_TEST(test_example);
  UNITY_END();
}
void loop() {}