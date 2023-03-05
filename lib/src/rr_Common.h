//!
//! @author M. Nickels
//! @brief Debug utilities for Arduino development
//!
//! @copyright Copyright (c) 2022
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

//! calculate size of an array
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

//! scan I2C bus and print result
void scanI2C(void);
