//!
//! @author M. Nickels
//! @brief unit test. Run tests with 'pio test -e test'
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

    intervall.printStatistics();

    TEST_ASSERT_UINT_WITHIN(1, period - 10, intervall.getMaxPeriod());
    TEST_ASSERT_UINT_WITHIN(1, period - 10, intervall.getMinPeriod());
    TEST_ASSERT_UINT_WITHIN(1, period - 10, intervall.getAvgPeriod());
}

// test a normal intervall with randomly wasted time
void test_random(void) {
    Intervall intervall(period);

    intervall.begin();

    for (unsigned loop = 0; loop < 10; loop++) {
        // waste some random time
        delay(random(period - 15, period - 4));

        TEST_ASSERT_EQUAL(Intervall::Success, intervall.wait());
    }

    intervall.printStatistics();

    TEST_ASSERT_UINT_WITHIN(6, period - 10, intervall.getMaxPeriod());
    TEST_ASSERT_UINT_WITHIN(6, period - 10, intervall.getMinPeriod());
    TEST_ASSERT_UINT_WITHIN(6, period - 10, intervall.getAvgPeriod());
}

// test an aborted intervall
bool abort_function(void) {
    return true;
}

void test_abort(void) {
    Intervall intervall(period);

    intervall.begin();

    for (unsigned loop = 0; loop < 10; loop++) {
        // waste some time
        delay(period - 10);

        TEST_ASSERT_EQUAL(Intervall::Abort, intervall.wait(abort_function));
    }

    intervall.printStatistics();
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

    intervall.printStatistics();

    TEST_ASSERT_UINT_WITHIN(1, period + 10, intervall.getMaxPeriod());
    TEST_ASSERT_UINT_WITHIN(1, period + 10, intervall.getMinPeriod());
    TEST_ASSERT_UINT_WITHIN(1, period + 10, intervall.getAvgPeriod());
}

// test failure without begin() before wait()
void test_no_begin(void) {
    Intervall intervall(period);

    TEST_ASSERT_EQUAL(Intervall::Failure, intervall.wait());
}

// test isPeriodOver()
void test_isPeriodOver(void) {
    Intervall intervall(period);

    intervall.begin();

    TEST_ASSERT_FALSE(intervall.isPeriodOver());

    delay(period);

    TEST_ASSERT_TRUE(intervall.isPeriodOver());
}

int runUnityTests(void) {
    Debug.beginSerial(115200);

    UNITY_BEGIN();

    // check return codes for wait function
    RUN_TEST(test_normal);
    RUN_TEST(test_random);
    RUN_TEST(test_abort);
    RUN_TEST(test_overflow);
    RUN_TEST(test_no_begin);
    RUN_TEST(test_isPeriodOver);

    return UNITY_END();
}

#ifdef ARDUINO

// embedded environment
void setup() {
    delay(2000);

    runUnityTests();
}

void loop() {
}

#else

// native environment
int main() {
    return runUnityTests();
}

#endif