//!
//! @file test_DebugUtils.cpp
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

//! @cond

void test_level_none(void) {
    Debug.setLevel(DebugUtils::None);

    TEST_ASSERT_FALSE(Debug.print(DebugUtils::None, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Error, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Warning, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Info, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Debug, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Verbose, __FUNCTION__, __LINE__, "Test", NULL));
}

void test_level_error(void) {
    Debug.setLevel(DebugUtils::Error);

    TEST_ASSERT_FALSE(Debug.print(DebugUtils::None, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Error, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Warning, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Info, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Debug, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Verbose, __FUNCTION__, __LINE__, "Test", NULL));
}

void test_level_warning(void) {
    Debug.setLevel(DebugUtils::Warning);

    TEST_ASSERT_FALSE(Debug.print(DebugUtils::None, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Error, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Warning, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Info, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Debug, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Verbose, __FUNCTION__, __LINE__, "Test", NULL));
}

void test_level_info(void) {
    Debug.setLevel(DebugUtils::Info);

    TEST_ASSERT_FALSE(Debug.print(DebugUtils::None, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Error, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Warning, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Info, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Debug, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Verbose, __FUNCTION__, __LINE__, "Test", NULL));
}

void test_level_debug(void) {
    Debug.setLevel(DebugUtils::Debug);

    TEST_ASSERT_FALSE(Debug.print(DebugUtils::None, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Error, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Warning, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Info, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Debug, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_FALSE(Debug.print(DebugUtils::Verbose, __FUNCTION__, __LINE__, "Test", NULL));
}

void test_level_verbose(void) {
    Debug.setLevel(DebugUtils::Verbose);

    TEST_ASSERT_FALSE(Debug.print(DebugUtils::None, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Error, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Warning, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Info, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Debug, __FUNCTION__, __LINE__, "Test", NULL));
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Verbose, __FUNCTION__, __LINE__, "Test", NULL));
}

int runUnityTests(void) {
    Debug.beginSerial(115200);

    UNITY_BEGIN();

    // check that default level is "verbose"
    TEST_ASSERT_TRUE(Debug.print(DebugUtils::Verbose, __FUNCTION__, __LINE__, "Test", NULL));

    // check all levels
    RUN_TEST(test_level_none);
    RUN_TEST(test_level_error);
    RUN_TEST(test_level_warning);
    RUN_TEST(test_level_info);
    RUN_TEST(test_level_debug);
    RUN_TEST(test_level_verbose);

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

using namespace fakeit;

// native environment
int main() {

    When(OverloadedMethod(ArduinoFake(Serial), begin, void(unsigned long))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t())).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char*))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), print, size_t(const char*))).AlwaysReturn();

    return runUnityTests();
}

#endif

//! @endcond
