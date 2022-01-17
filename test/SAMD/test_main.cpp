
#include <Arduino.h>
#include <unity.h>

#include "rr_SAMDUtils.h"

void test_true(void) {
    TEST_ASSERT_TRUE(true);
}

void setup() {
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_true);
    UNITY_END();
}

void loop() {
}