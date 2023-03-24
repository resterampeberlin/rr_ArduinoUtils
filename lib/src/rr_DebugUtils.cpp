//!
//! @file rr_DebugUtils.cpp
//! @author M. Nickels
//! @brief Debug utilities for Arduino development
//!
//! This file is part of the Library "rr_ArduinoUtils".
//!
//! This work is licensed under the
//!
//!      Creative Commons Attribution-ShareAlike 4.0 International License.
//!
//! To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/
//! or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
//!
//! This work has been inspired by the library "Arduino_DebugUtils"
//! See https://github.com/arduino-libraries/Arduino_DebugUtils
//!

#include <Arduino.h>
#include <stdarg.h>

// own includes
#include "rr_DebugUtils.h"

//! our unique Debug object, only declared in debug build
#ifdef __PLATFORMIO_BUILD_DEBUG__
DebugUtils Debug;
#endif

const char* GITversion(void) {
#ifdef GIT_VERSION
    return GIT_VERSION;
#else
    #pragma message("GIT_VERSION not defined")
    return "undefined";
#endif
}

DebugUtils::DebugUtils() {
#ifdef ARDUINO
    setOutput(&Serial);
#else
    setOutput(NULL);
#endif

    setLevel(Verbose);
}

void DebugUtils::beginSerial(unsigned long baud, unsigned timeout) {
    unsigned loop = 0;

#ifdef ARDUINO
    if (output) {
        // Init serial communication
        output->begin(baud);

        while (!*output && loop < timeout) {
            delay(100);
            loop++;
        }
    }
#endif
}

const char* DebugUtils::getInfoMarking(DebugLevel_t level) {
    const char* result = NULL;

    switch (level) {
    case None:
        result = "";
        break;
    case Info:
        result = ANSI_GREEN_FG "I:";
        break;
    case Verbose:
        result = ANSI_NORMAL "V:";
        break;
    case Debug:
        result = ANSI_BLUE_FG "D:";
        break;
    case Warning:
        result = ANSI_YELLOW_FG "W:";
        break;
    case Error:
        result = ANSI_RED_BG "E:";
        break;
    }

    return result;
}

const char* DebugUtils::getTextMarking(DebugLevel_t level) {
    const char* result = NULL;

    switch (level) {
    case Error:
        result = ANSI_RED_BG;
        break;
    case Warning:
        result = ANSI_YELLOW_FG;
        break;
    default:
        result = ANSI_NORMAL;
        break;
    }

    return result;
}

bool DebugUtils::print(DebugLevel_t level, const char* location, unsigned line, const char* fmt, ...) {
    if (shouldPrint(level) && output) {
        va_list args;
        char    text[128];

        // print diagnostic information
        snprintf(text, sizeof(text), "%s %s:%d" ANSI_NORMAL "\t", getInfoMarking(level), location, line);

        output->print(text);
        output->print(getTextMarking(level));

        // print formatted text
        va_start(args, fmt);
        vsnprintf(text, sizeof(text), fmt, args);
        va_end(args);

        output->print(text);
        output->println(ANSI_NORMAL);

        return true;
    }
    else {
        return false;
    }
}

bool DebugUtils::print(DebugLevel_t level, const char* location, unsigned line, const __FlashStringHelper* fmt, ...) {
    if (shouldPrint(level) && output) {
        va_list args;
        char    text[128];
        String  fmt_str(fmt);

        // print diagnostic information
        snprintf(text, sizeof(text), "%s %s:%d" ANSI_NORMAL "\t", getInfoMarking(level), location, line);
        output->print(text);
        output->print(getTextMarking(level));

        // print formatted text
        va_start(args, fmt);
        vsnprintf(text, sizeof(text), fmt_str.c_str(), args);
        va_end(args);

        output->print(text);
        output->println(ANSI_NORMAL);

        return true;
    }
    else {
        return false;
    }
}

void DebugUtils::setTab(unsigned column) {
    if (output) {
        char text[20];

        output->print(ANSI_CLEARTABS);

        snprintf(text, sizeof(text), ANSI_ESC "[%dC" ANSI_SETTAB, column);
        output->println(text);
    }
}

void DebugUtils::setTabs(unsigned columns[], unsigned count) {
    if (output) {
        output->print(ANSI_CLEARTABS);

        for (unsigned loop = 0, lastTab = 0; loop < count; loop++) {
            char text[20];

            snprintf(text, sizeof(text), ANSI_ESC "[%dC" ANSI_SETTAB, columns[loop] - lastTab);
            output->println(text);

            lastTab = columns[loop];
        }

        output->println();
    }
}

void DebugUtils::clearTabs(void) {
    if (output) {
        output->print(ANSI_CLEARTABS);
    }
}

void DebugUtils::setLevel(DebugLevel_t level) {
    currentLevel = level;
}

void DebugUtils::setOutput(HardwareSerial* toSerial) {
    output = toSerial;
}

bool DebugUtils::shouldPrint(DebugLevel_t level) {
    return level <= currentLevel && level != None;
}