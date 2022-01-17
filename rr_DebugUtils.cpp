//!
//! @file rr_DebugUtils.cpp
//! @author M. Nickels
//! @brief Debug utilities for Arduino developtment
//! @version 0.1
//! @date 14.1.2022
//!
//! @copyright Copyright (c) 2022
//!
//! This file is part of the Application "rr_ArduinoUtils".
//!
//! rr_ArduinoUtilsis free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 3 of the License, or
//! (at your option) any later version.
//!
//! rr_ArduinoUtils is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with rr_ArduinoUtils.  If not, see <http://www.gnu.org/licenses/>.
//!

#include <Arduino.h>
#include <stdarg.h>

//! own includes
#include "rr_DebugUtils.h"

//! our unique Debug object
DebugUtils Debug;

//!
//! @brief Construct a new Debug Utils:: Debug Utils object
//! set output stream and debug level to default values
//!
DebugUtils::DebugUtils() {
    setDebugOutputStream(&Serial);
    setDebugLevel(Verbose);
}

//!
//! @brief get the markings (text, color) for the debug informatinon
//! depending from the debug level
//!
//! @param level the debug level
//! @return the marking, may include ANSI escape sequences
//!
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
        result = ANSI_YELLOW_BG "W:";
        break;
    case Error:
        result = ANSI_RED_BG "E:";
        break;
    }

    return result;
}

//!
//! @brief get the markings (text, color) for the text
//! depending from the debug level
//!
//! @param level the debug level
//! @return the marking, may include ANSI escape sequences
//!
const char* DebugUtils::getTextMarking(DebugLevel_t level) {
    const char* result = NULL;

    switch (level) {
    case Error:
        result = ANSI_RED_BG;
        break;
    case Warning:
        result = ANSI_YELLOW_BG;
        break;
    default:
        result = ANSI_NORMAL;
        break;
    }

    return result;
}

//! generic print routine
void DebugUtils::print(DebugLevel_t level, const char* function, unsigned line, const char* fmt, ...) {
    if (shouldPrint(level) && output) {
        va_list args;
        char    text[256];

        // print diagnostic information
        snprintf(text, sizeof(text), "%s %s:%d\t", getInfoMarking(level), function, line);
        output->print(text);
        output->print(getTextMarking(level));

        // print formatted text
        va_start(args, fmt);
        vsnprintf(text, sizeof(text), fmt, args);
        output->print(text);
        va_end(args);

        output->println(ANSI_NORMAL);
    }
}

void DebugUtils::print(DebugLevel_t level, const char* function, unsigned line, const __FlashStringHelper* fmt, ...) {
    if (shouldPrint(level) && output) {
        va_list args;
        char    text[256];
        String  fmt_str(fmt);

        // print diagnostic information
        snprintf(text, sizeof(text), "%s %s:%d" ANSI_NORMAL "\t", getInfoMarking(level), function, line);
        output->print(text);
        output->print(getTextMarking(level));

        // print formatted text
        vsnprintf(text, sizeof(text), fmt_str.c_str(), args);
        output->print(text);
        va_end(args);

        output->println(ANSI_NORMAL);
    }
}

//!
//! @brief set the first tab for the output.
//!
//! @param column column for the tab
//!
void DebugUtils::setTab(unsigned column) {
    if (output) {
        char text[20];

        snprintf(text, sizeof(text), ANSI_CLEARTABS ANSI_ESC "[%dC" ANSI_SETTAB, column);
        output->println(text);
    }
}

//!
//! @brief set the maximum level of output
//!
//! @param level the maximum level
//!
void DebugUtils::setDebugLevel(DebugLevel_t level) {
    currentLevel = level;
}

//!
//! @brief assign an output stream
//!
//! @param stream pointer to the stream
//!
void DebugUtils::setDebugOutputStream(Stream* stream) {
    output = stream;
}

//!
//! @brief derive, if a message has to be printed
//!
//! @param level the debug level
//! @return true if debug level is lower/equal than current debug level
//! @return false otherwise
//!
bool DebugUtils::shouldPrint(DebugLevel_t level) {
    return level <= currentLevel;
}
