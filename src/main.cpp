//!
//! @file main.cpp
//! @author M. Nickels
//! @brief Main file for the Library "rr_ArduinoUtils"
//!

//! This work is licensed under the
//!
//!      Creative Commons Attribution-NonCommercial 4.0 International License.
//!
//! To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/
//! or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
//!

#include <Arduino.h>

// own includes
#include "rr_Common.h"
#include "rr_DebugUtils.h"
#include "rr_Intervall.h"

Intervall intervall; //!< 500 ms intervall

//!
//! @brief Setup routine
//!
void setup() {
#ifdef DEBUG
    // start debugging on serial
    Debug.beginSerial();

    // set a tab on column 30 to increase monitor output formatting
    Debug.setTab(15);
#endif

    PRINT_BUILD();

    PRINT_VERBOSE("Verbose", NULL);
    PRINT_DEBUG("Debug", NULL);
    PRINT_INFO("Info", NULL);
    PRINT_WARNING("Warning", NULL);
    PRINT_ERROR("Error", NULL);

    intervall.begin();
    delay(100);
    intervall.wait();
}

//!
//! @brief Main loop
//!
void loop() {
}