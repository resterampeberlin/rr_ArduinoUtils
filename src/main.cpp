//!
//! @file main.cpp
//! @author M. Nickels
//! @brief Main file for the Library "rr_ArduinoUtils"
//! @version 0.1
//! @date 2021-12-20
//!
//! @copyright Copyright (c) 2021
//!
//! This file is part of the the Library "rr_ArduinoUtils".
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

#include <Arduino.h>

//! own includes
#include "rr_DebugUtils.h"

//!
//! @brief Setup routine
//!
void setup() {
    unsigned loop = 0;

    // Init serial communication
    Serial.begin(115200);

    while (!Serial && loop < 500) {
        delay(100);
        loop++;
    }

    // set a tab on column 30 to increase monitor output formatting
    Debug.setTab(30);
    PRINT_BUILD();

    PRINT_VERBOSE("Verbose", NULL);
    PRINT_DEBUG("Debug", NULL);
    PRINT_INFO("Info", NULL);
    PRINT_WARNING("Warning", NULL);
    PRINT_ERROR("Error", NULL);

    PRINT_DEBUG("An integer: %d  unsigned: %u  float: %f   string: %s", -1234, 2345, 5678.9, "a string");
}

//!
//! @brief Main loop
//!
void loop() {
}