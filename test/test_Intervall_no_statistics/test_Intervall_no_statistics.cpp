//!
//! @file test_Intervall_no_statistics.cpp
//! @author M. Nickels
//! @brief unit test
//! @note Run tests with 'pio test -e test_no_statistics'
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

//! @cond

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

int runUnityTests(void) {
    Debug.beginSerial(115200);

    delay(2000);

    UNITY_BEGIN();

    // check return codes for wait function
    RUN_TEST(test_normal);
    RUN_TEST(test_overflow);

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
    #include <chrono>
    #include <unistd.h>

using namespace std::chrono;
using namespace fakeit;

long myRandom(long a, long b) {
    long r = rand() % (b - a + 1) + a;

    // TEST_PRINTF("r = %d", r);

    return r;
}

unsigned long myMillis(void) {
    unsigned long t = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    // TEST_PRINTF("t = %d", t);

    return t;
}

void mySleep(unsigned long t) {
    usleep(t * 1000);
}

// native environment
int main() {
    When(OverloadedMethod(ArduinoFake(), random, long(long, long))).AlwaysDo([](long a, long b) -> long {
        return myRandom(a, b);
    });
    When(Method(ArduinoFake(), delay)).AlwaysDo([](unsigned long t) -> void { return mySleep(t); });
    When(Method(ArduinoFake(), millis)).AlwaysDo([](void) -> unsigned long { return myMillis(); });

    When(Method(ArduinoFake(), yield)).AlwaysReturn();

    When(OverloadedMethod(ArduinoFake(Serial), begin, void(unsigned long))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t())).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char*))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), print, size_t(const char*))).AlwaysReturn();

    return runUnityTests();
}

#endif

//! @endcond