//!
//! @file rr_DebugUtils.h
//! @author M. Nickels
//! @brief Debug utilities for Arduino development
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

// own includes

#ifndef RR_DEBUG_NOCOLORS

//!
//! @name ANSI escape sequences
//! @details ANSI escape codes for the terminal window
//!          use "monitor_flags = --raw" in platformio.ini
//!          for a detailed definition see https://en.wikipedia.org/wiki/ANSI_escape_code
//! @{

    #define ANSI_ESC       "\033"             //!< Escape code
    #define ANSI_GREEN_FG  ANSI_ESC "[32m"    //!< Print green foreground
    #define ANSI_BLUE_FG   ANSI_ESC "[34m"    //!< Print blue foreground
    #define ANSI_YELLOW_FG ANSI_ESC "[33m"    //!< Print yellow foreground
    #define ANSI_RED_BG    ANSI_ESC "[41m"    //!< Print red background
    #define ANSI_NORMAL    ANSI_ESC "[39;49m" //!< Print normal foreground/background
    #define ANSI_CLEARTABS ANSI_ESC "[3g"     //!< clear all tabs
    #define ANSI_SETTAB    ANSI_ESC "H"       //!< set tab at current cursor position

//! @}
#else
//! @cond
    #define ANSI_ESC       ""
    #define ANSI_GREEN_FG  ""
    #define ANSI_BLUE_FG   ""
    #define ANSI_YELLOW_FG ""
    #define ANSI_RED_BG    ""
    #define ANSI_NORMAL    ""
    #define ANSI_CLEARTABS ""
    #define ANSI_SETTAB    ""
//! @endcond
#endif

//! date and time when this module was built
#define BUILD __DATE__ " " __TIME__

//! print current build
#define PRINT_BUILD()                                                                                                  \
    PRINT_INFO("Build: " ANSI_GREEN_FG "%s" ANSI_NORMAL "  Git version: " ANSI_GREEN_FG "%s" ANSI_NORMAL, BUILD,       \
               GITversion())

//!
//! @brief return current git version
//!
//! @return const char* current version
//!
const char* GITversion(void);

//!
//! @brief this class encapsulates the debug output functions
//!
//!
class DebugUtils {

  public:
    //!
    //! @brief Available reporting levels
    //!
    typedef enum {
        None,    //!< no output at all
        Error,   //!< error messages, appear in red
        Warning, //!< warning messages
        Info,    //!< general information
        Debug,   //!< debug message
        Verbose  //!< everything else
    } DebugLevel_t;

    //!
    //! @brief Construct a new Debug Utils:: Debug Utils object
    //! set output stream and debug level to default values
    //!
    DebugUtils();

    //! start output to serial
    void beginSerial(unsigned long baud = 115200, unsigned timeout = 50);

    //!
    //! @brief generic print routine
    //!
    //! @param level debug level
    //! @param location where does the print come from (file, function)
    //! @param line line number
    //! @param fmt format specification
    //! @param ... parameters
    //! @return true if parameter level is lower/equal current debug level
    //! @return false otherwise (message was not printed)
    //!
    bool print(DebugLevel_t level, const char* location, unsigned line, const __FlashStringHelper* fmt, ...);

    //!
    //! @brief set the first tab for the output.
    //!
    //! @param column column for the tab
    //!
    void setTab(unsigned column);

    //!
    //! @brief sets a number of tabs for the output
    //!
    //! @param columns array, which contains ascending tab position in absolute columns
    //! @param count number of tabs
    //!
    void setTabs(unsigned columns[], unsigned count);

    //!
    //! @brief clear all tabs in output
    //!
    void clearTabs(void);

    //!
    //! @brief set the maximum level of output
    //!
    //! @param level the maximum level
    //!
    void setLevel(DebugLevel_t level);

    //!
    //! @brief assign an output stream
    //!
    //! @param toSerial pointer to the serial port
    //!
    void setOutput(HardwareSerial* toSerial);

  private:
    DebugLevel_t    currentLevel; //!< current debug level
    HardwareSerial* output;       //!< pointer to serial interface, where print goes to

    //!
    //! @brief derive, if a message has to be printed
    //!
    //! @param level the debug level
    //! @return true if debug level is lower/equal than current debug level
    //! @return false otherwise
    //!
    bool shouldPrint(DebugLevel_t level);

    //!
    //! @brief get the markings (text, color) for the debug informatinon
    //! depending from the debug level
    //!
    //! @param level the debug level
    //! @return the marking, may include ANSI escape sequences
    //!
    const char* getInfoMarking(DebugLevel_t level);

    //!
    //! @brief get the markings (text, color) for the text
    //! depending from the debug level
    //!
    //! @param level the debug level
    //! @return the marking, may include ANSI escape sequences
    //!
    const char* getTextMarking(DebugLevel_t level);
};

// following functions are only available/executed in a debug build
#ifdef __PLATFORMIO_BUILD_DEBUG__

extern DebugUtils Debug; //!< ebug object only present in debug builds

    //!
    //! @brief set file display in PRINT_ function
    //! @details use the following valus to save memory or make the output exhaustive.
    //!          e.g.set `-D RR_DEBUG_LOCATION = 1` globally in `platformio.ini` or place a
    //!          `#define RR_DEBUG_LOCATION = 1` locally before including rr_DebugUtils.h
    //!
    //!          Value | Description
    //!          ----- | -----------
    //!          0     | no output (least memory consumption)
    //!          1     | print only the file
    //!          empty | print function name (highest memory consumption)
    //!
    #ifndef RR_DEBUG_LOCATION
        #define RR_DEBUG_LOCATION 1
    #endif

    //!
    //! @brief derive location based on #RR_DEBUG_LOCATION
    //!
    #if RR_DEBUG_LOCATION == 0
        #define RR_DEBUG_LOC ""
    #elif RR_DEBUG_LOCATION == 1
        #define RR_DEBUG_LOC __FILE__
    #else
        #define RR_DEBUG_LOC __FUNCTION__
    #endif

//!
//! @name Debug print routines
//! @param text format specification
//! @param ... parameters for format string
//! @details You must provide at least one paramter. Use NULL if there is nothing to format.
//!          The format specification must be a string literal (e.g. "a:%s") because it is converted to a
//!          F(fmt) FlashStringHelper type. If you want to print a non literal use `PRINT_INFO("%s", s)` or
//!          `PRINT_INFO("%s", s.c_str())`.
//!          If you use "%f" in format specification you must use specific compiler flags for certain MCUs (UNO, NANO)
//!          e.g. `build_flags = -Wl,-u,vfprintf -lprintf_flt -lm`
//! @{

    #define PRINT_INFO(text, ...)    Debug.print(DebugUtils::Info, RR_DEBUG_LOC, __LINE__, F(text), __VA_ARGS__)
    #define PRINT_DEBUG(text, ...)   Debug.print(DebugUtils::Debug, RR_DEBUG_LOC, __LINE__, F(text), __VA_ARGS__)
    #define PRINT_VERBOSE(text, ...) Debug.print(DebugUtils::Verbose, RR_DEBUG_LOC, __LINE__, F(text), __VA_ARGS__)
    #define PRINT_WARNING(text, ...) Debug.print(DebugUtils::Warning, RR_DEBUG_LOC, __LINE__, F(text), __VA_ARGS__)
    #define PRINT(text, ...)         Debug.print(DebugUtils::Verbose, RR_DEBUG_LOC, __LINE__, F(text), __VA_ARGS__)
    #define PRINT_ERROR(text, ...)   Debug.print(DebugUtils::Error, RR_DEBUG_LOC, __LINE__, F(text), __VA_ARGS__)

//! @}

    //! @brief evaluate expression and print message if evals to false
    #define VERIFY(expression)                                                                                         \
        if (!(expression)) {                                                                                           \
            PRINT_ERROR("ERROR, verify failed", NULL);                                                                 \
        }

    //! @brief evaluate expression and print message if evals to false
    #define ASSERT(expression)                                                                                         \
        if (!(expression)) {                                                                                           \
            PRINT_ERROR("ERROR, assertion failed", NULL);                                                              \
        }

    //! @brief evaluate if expression lies with in given range
    #define ASSERT_BETWEEN(expression, low, high)                                                                      \
        if (!((expression) >= (low) && (expression) <= (high))) {                                                      \
            PRINT_ERROR("ERROR, assertion failed", NULL);                                                              \
        }

    //! @brief evaluate if expression lies with in given range
    #define ASSERT_ARRAYINDEX(array, index)                                                                            \
        if (!((index) >= 0 && (index) < ARRAY_SIZE(array))) {                                                          \
            PRINT_ERROR("ERROR, assertion failed", NULL);                                                              \
        }

    //! @brief display a "tracepoint" (file, linenumber, text "---")
    #define TP() PRINT_DEBUG("---", NULL)
#else
//! @cond
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

    #define VERIFY(expression) expression
//! @endcond
#endif
