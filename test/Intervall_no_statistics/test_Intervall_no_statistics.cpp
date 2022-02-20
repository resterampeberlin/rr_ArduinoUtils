// runt this test with
// pio test -c test/Intervall_no_statistics/no_statistics.ini -v

#include <Arduino.h>
#include <unity.h>

#include "rr_DebugUtils.h"
#include "rr_Intervall.h"

const unsigned int period = 500; // 500 milliss

// test a normal intervall
void test_normal(void) {
    Intervall intervall(period);

    intervall.begin();

    for (unsigned loop = 0; loop < 10; loop++) {
        unsigned int start = millis();

        // t = 0
        TEST_ASSERT_UINT_WITHIN(1, 0, millis() - start);

        // waste some time
        delay(period - 10);

        // t = period- 10
        TEST_ASSERT_UINT_WITHIN(1, period - 10, millis() - start);

        TEST_ASSERT_EQUAL(Intervall::Success, intervall.wait());

        // t = period
        TEST_ASSERT_UINT_WITHIN(1, period, millis() - start);
    }
}

// test overflowed intervall
void test_overflow(void) {
    Intervall intervall(period);

    intervall.begin();

    for (unsigned loop = 0; loop < 10; loop++) {
        // waste more time than expected
        delay(period + 10);

        TEST_ASSERT_EQUAL(Intervall::Overflow, intervall.wait());
    }
}

void setup() {
    delay(2000);

    UNITY_BEGIN();

    // check return codes for wait function
    RUN_TEST(test_normal);
    RUN_TEST(test_overflow);

    UNITY_END();
}

void loop() {
}