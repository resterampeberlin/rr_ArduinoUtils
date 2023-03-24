//!
//! @file test_scanI2C.cpp
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
#include <Wire.h>
#include <unity.h>

#include "rr_Common.h"
#include "rr_DebugUtils.h"

//! @cond

void test_noDevice(void) {
    TEST_ASSERT_EQUAL(scanI2C(), 0);
}

int runUnityTests(void) {
    Debug.setOutput(NULL);
    Wire.begin();

    UNITY_BEGIN();

    // check all levels
    RUN_TEST(test_noDevice);

    return UNITY_END();
}

// embedded environment
void setup() {
    delay(2000);

    runUnityTests();
}

void loop() {
}

//! @endcond
