//!
//! @author M. Nickels
//! @brief Debug utilities for Arduino development
//!
//! @copyright Copyright (c) 2023
//!
//! This file is part of the library "rr_ArduinoUtils".
//!
//!      Creative Commons Attribution-ShareAlike 4.0 International License.
//!
//! To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/
//! or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
//!
//! This work has been inspired by the library "Arduino_DebugUtils"
//! See https://github.com/arduino-libraries/Arduino_DebugUtils
//!

#pragma once

#include <Arduino.h>

//! own includes

//! ANSI escape codes for the terminal window
//! use "monitor_flags = --raw" in platformio.ini
//! for a detailed definition see
//! https://en.wikipedia.org/wiki/ANSI_escape_code

#ifndef RR_DEBUG_NOCOLORS

    #define ANSI_ESC       "\033"             //!< Escape code
    #define ANSI_GREEN_FG  ANSI_ESC "[32m"    //!< Print green foreground
    #define ANSI_BLUE_FG   ANSI_ESC "[34m"    //!< Print blue foreground
    #define ANSI_YELLOW_FG ANSI_ESC "[33m"    //!< Print yellow foreground
    #define ANSI_RED_BG    ANSI_ESC "[41m"    //!< Print red background
    #define ANSI_NORMAL    ANSI_ESC "[39;49m" //!< Print normal foreground/background
    #define ANSI_CLEARTABS ANSI_ESC "[3g"     //!< clear all tabs
    #define ANSI_SETTAB    ANSI_ESC "H"       //!< set tab at current cursor position

#else

    #define ANSI_ESC       ""
    #define ANSI_GREEN_FG  ""
    #define ANSI_BLUE_FG   ""
    #define ANSI_YELLOW_FG ""
    #define ANSI_RED_BG    ""
    #define ANSI_NORMAL    ""
    #define ANSI_CLEARTABS ""
    #define ANSI_SETTAB    ""

#endif

//! date and time when this module was built
#define BUILD __DATE__ " " __TIME__

//! print current build
#define PRINT_BUILD()                                                                                                  \
    PRINT_INFO("Build: " ANSI_GREEN_FG "%s" ANSI_NORMAL "  Git version: " ANSI_GREEN_FG "%s" ANSI_NORMAL, BUILD,       \
               GITversion())

const char* GITversion(void);

//!
//! @brief this class encapsulates the debug output functions
//!
//!
class DebugUtils {

  public:
    //! Available reporting levels
    typedef enum { None, Error, Warning, Info, Debug, Verbose } DebugLevel_t;

    //! Constructor
    DebugUtils();

    //! start output to serial
    void beginSerial(unsigned long baud = 115200, unsigned timeout = 50);

    //! generic print routines
    bool print(DebugLevel_t level, const char* location, unsigned line, const char* fmt, ...);
    bool print(DebugLevel_t level, const char* location, unsigned line, const __FlashStringHelper* fmt, ...);

    void setTab(unsigned column);
    void setTabs(unsigned columns[], unsigned count);
    void clearTabs(void);

    void setLevel(DebugLevel_t level);
    void setOutput(HardwareSerial* toSerial);

  private:
    DebugLevel_t    currentLevel;
    HardwareSerial* output;

    bool            shouldPrint(DebugLevel_t level);
    const char*     getInfoMarking(DebugLevel_t level);
    const char*     getTextMarking(DebugLevel_t level);
};

// following functions are only available/executed in a debug build
#ifdef __PLATFORMIO_BUILD_DEBUG__

//! debug object only present in debug builds
extern DebugUtils Debug;

    // set file display as default
    #ifndef RR_DEBUG_LOCATION
        #define RR_DEBUG_LOCATION 1
    #endif

    //! select location depending on option
    //! 0 no informatin to save maximum RAM
    //! 1 only filenme
    //! others function name (consumes most RAM)
    #if RR_DEBUG_LOCATION == 0
        #define RR_DEBUG_LOC ""
    #elif RR_DEBUG_LOCATION == 1
        #define RR_DEBUG_LOC __FILE__
    #else
        #define RR_DEBUG_LOC __FUNCTION__
    #endif

    #define PRINT_INFO(text, ...)    Debug.print(DebugUtils::Info, RR_DEBUG_LOC, __LINE__, text, __VA_ARGS__)
    #define PRINT_DEBUG(text, ...)   Debug.print(DebugUtils::Debug, RR_DEBUG_LOC, __LINE__, text, __VA_ARGS__)
    #define PRINT_VERBOSE(text, ...) Debug.print(DebugUtils::Verbose, RR_DEBUG_LOC, __LINE__, text, __VA_ARGS__)
    #define PRINT_WARNING(text, ...) Debug.print(DebugUtils::Warning, RR_DEBUG_LOC, __LINE__, text, __VA_ARGS__)
    #define PRINT(text, ...)         Debug.print(DebugUtils::Verbose, RR_DEBUG_LOC, __LINE__, text, __VA_ARGS__)
    #define PRINT_ERROR(text, ...)   Debug.print(DebugUtils::Error, RR_DEBUG_LOC, __LINE__, text, __VA_ARGS__)

    //! evaluate expression and print message if evals to false
    #define VERIFY(expression)                                                                                         \
        if (!(expression)) {                                                                                           \
            PRINT_ERROR(F("ERROR, verify failed"), NULL);                                                              \
        }

    //! evaluate expression and print message if evals to false
    #define ASSERT(expression)                                                                                         \
        if (!(expression)) {                                                                                           \
            PRINT_ERROR(F("ERROR, assertion failed"), NULL);                                                           \
        }

    //! evaluate if expression lies with in given range
    #define ASSERT_BETWEEN(expression, low, high)                                                                      \
        if (!((expression) >= (low) && (expression) <= (high))) {                                                      \
            PRINT_ERROR(F("ERROR, assertion failed"), NULL);                                                           \
        }

    //! evaluate if expression lies with in given range
    #define ASSERT_ARRAYINDEX(array, index)                                                                            \
        if (!((index) >= 0 && (index) < ARRAY_SIZE(array))) {                                                          \
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
    #define PRINT_ERROR(text, ...)
    #define PRINT(text, ...)
    #define ASSERT(expression)
    #define ASSERT_BETWEEN(expression, low, high)
    #define ASSERT_ARRAYINDEX(array, index)

    #define TP()

    // simply execute exp
    #define VERIFY(expression) expression
#endif
