//!
//! @file rr_scanI2C.cpp
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
#include <Wire.h>

// own includes
#include "rr_DebugUtils.h"

//!
//! @brief scan I2C bus and show devices
//!
//! @return uint8_t number of found devices
//!
uint8_t scanI2C(void) {
    byte    error, address; // variable for error and I2C address
    uint8_t nDevices;

    PRINT_INFO("Scanning...", NULL);

    nDevices = 0;
    for (address = 1; address < 127; address++) {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            PRINT_INFO("I2C device 0x%x", address);
            nDevices++;
        }
        else if (error == 4) {
            PRINT_WARNING("I2C error 0x%x", address);
        }
    }
    if (nDevices == 0)
        PRINT_WARNING("No I2C devices found", NULL);
    else
        PRINT_INFO("done", NULL);

    return nDevices;
}