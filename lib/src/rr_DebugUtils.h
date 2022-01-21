//!
//! @file rr_DebugUtils.h
//! @author M. Nickels
//! @brief Debug utilities for Arduino development
//! @version 0.1
//! @date 2021-12-20
//!
//! @copyright Copyright (c) 2022
//!
//! This file is part of the Application "rr_ArduinoUtils".
//!
//! rr_ArduinoUtils is free software: you can redistribute it and/or modify
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

#pragma once

//! ANSI escape codes for the terminal window
//! use "monitor_flags = --raw" in platformio.ini
#define ANSI_ESC       "\033"

#define ANSI_GREEN_FG  ANSI_ESC "[32m"
#define ANSI_BLUE_FG   ANSI_ESC "[34m"
#define ANSI_YELLOW_FG ANSI_ESC "[33m"
#define ANSI_RED_BG    ANSI_ESC "[41m"
#define ANSI_NORMAL    ANSI_ESC "[39;49m"

#define ANSI_CLEARTABS ANSI_ESC "[3g"
#define ANSI_SETTAB    ANSI_ESC "H"

//! date and time when this module was built
#define BUILD          __DATE__ " " __TIME__

#define PRINT_BUILD()                                                                                                  \
    PRINT_INFO("Build: " ANSI_GREEN_FG "%s" ANSI_NORMAL "  Git version: " ANSI_GREEN_FG "%s" ANSI_NORMAL, BUILD,       \
               GITversion())

const char* GITversion(void);

class DebugUtils {

  public:
    //! Available reporting levels
    typedef enum { None, Error, Warning, Info, Debug, Verbose } DebugLevel_t;

    //! Constructor
    DebugUtils();

    //! generic print routines
    bool print(DebugLevel_t level, const char* function, unsigned line, const char* fmt, ...);
    bool print(DebugLevel_t level, const char* function, unsigned line, const __FlashStringHelper* fmt, ...);

    void setTab(unsigned column);
    void setDebugLevel(DebugLevel_t level);
    void setDebugOutputStream(Stream* stream);

  private:
    DebugLevel_t currentLevel;
    Stream*      output;

    bool         shouldPrint(DebugLevel_t level);
    const char*  getInfoMarking(DebugLevel_t level);
    const char*  getTextMarking(DebugLevel_t level);
};

extern DebugUtils Debug;

// this function is always executed
#define PRINT_ERROR(text, ...) Debug.print(DebugUtils::Error, __FUNCTION__, __LINE__, text, __VA_ARGS__)

// following functions are only available/executed in a debug build
#ifdef __PLATFORMIO_BUILD_DEBUG__
    #define PRINT_INFO(text, ...)    Debug.print(DebugUtils::Info, __FUNCTION__, __LINE__, text, __VA_ARGS__)
    #define PRINT_DEBUG(text, ...)   Debug.print(DebugUtils::Debug, __FUNCTION__, __LINE__, text, __VA_ARGS__)
    #define PRINT_VERBOSE(text, ...) Debug.print(DebugUtils::Verbose, __FUNCTION__, __LINE__, text, __VA_ARGS__)
    #define PRINT_WARNING(text, ...) Debug.print(DebugUtils::Warning, __FUNCTION__, __LINE__, text, __VA_ARGS__)
    #define PRINT(text, ...)         Debug.print(DebugUtils::Verbose, __FUNCTION__, __LINE__, text, __VA_ARGS__)

    // evaluate expression and print message if evals to false
    #define VERIFY(expression)                                                                                         \
        if (!(expression)) {                                                                                           \
            PRINT_ERROR(F("ERROR, verify failed"), NULL);                                                              \
        }

    #define ASSERT(expression)                                                                                         \
        if (!(expression)) {                                                                                           \
            PRINT_ERROR(F("ERROR, assertion failed"), NULL);                                                           \
        }

    // display a "tracepoint"
    #define TP() PRINT_DEBUG("---", NULL)
#else
    // disable these functions in order to save code space and execution time
    #define PRINT_INFO(text, ...)
    #define PRINT_DEBUG(text, ...)
    #define PRINT_VERBOSE(text, ...)
    #define PRINT_WARNING(text, ...)
    #define PRINT(text, ...)
    #define ASSERT(expression)

    #define TP()

    // simply execute exp
    #define VERIFY(expression) expression
#endif
