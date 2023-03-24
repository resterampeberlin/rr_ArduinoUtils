//!
//! @file test_Common.cpp
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

//! code under test
#include "rr_Common.h"

void test_Macros(void) {
    int         intArray[]    = {1, 2, 3};
    const char* stringArray[] = {"one", "two"};
    int         emptyArray[]  = {};

    TEST_ASSERT_EQUAL(3, ARRAY_SIZE(intArray));
    TEST_ASSERT_EQUAL(2, ARRAY_SIZE(stringArray));
    TEST_ASSERT_EQUAL(0, ARRAY_SIZE(emptyArray));
}

int runUnityTests(void) {
    UNITY_BEGIN();

    RUN_TEST(test_Macros);

    UNITY_END();

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