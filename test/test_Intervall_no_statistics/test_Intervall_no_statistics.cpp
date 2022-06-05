//!
//! @author M. Nickels
//! @brief unit test. Run tests with 'pio test -e test_no_statistics'
//!
//! @copyright Copyright (c) 2022
//!
//! This file is part of the Application "rr_ArduinoUtils".
//!
//!      Creative Commons Attribution-ShareAlike 4.0 International License.
//!
//! To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/
//! or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
//!

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
    Debug.beginSerial(115200);

    delay(2000);

    UNITY_BEGIN();

    // check return codes for wait function
    RUN_TEST(test_normal);
    RUN_TEST(test_overflow);

    UNITY_END();
}

void loop() {
}