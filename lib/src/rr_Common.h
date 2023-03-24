//!
//! @file rr_Common.h
//! @author M. Nickels
//! @brief Debug utilities for Arduino development
//!
//! This file is part of the Application "rr_ArduinoUtils".
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

//! @brief calculate size of an array
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

//!
//! @brief  scan I2C bus and print result
//!
//! @return number of devices on I2C bus
//! @pre call Wire.begin before calling this function
//!
uint8_t scanI2C(void);
