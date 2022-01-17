//!
//! @file rr_Intervall.cpp
//! @author M. Nickels
//! @brief usefull class to work with intervalls/periodic execution
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
#include <limits.h>

//! own includes
#include "rr_Intervall.h"

Intervall::Intervall() {
    maxPeriod = 0;
    minPeriod = ULONG_MAX;
    timeStamp = millis();

    // assume a default og 100ms
    setPeriod(100);
}

Intervall::Intervall(unsigned long newPeriod) : Intervall() {
    setPeriod(newPeriod);
}

void Intervall::setPeriod(unsigned long newPeriod) {
    period = newPeriod;
}

void Intervall::begin(void) {
    timeStamp = millis();
}

Intervall::Result_t Intervall::wait(bool (*userFunc)(void)) {
    unsigned long delta  = millis() - timeStamp;
    Result_t      result = Success;

    minPeriod            = min(minPeriod, delta);
    maxPeriod            = max(maxPeriod, delta);

    if (delta < period) {
        while (millis() - timeStamp < period) {
            if (userFunc != NULL && userFunc()) {
                result = Abort;
                break;
            }

            yield();
        }
    }
    else {
        result = Overflow;
    }

    timeStamp = millis();

    return result;
}

unsigned long Intervall::getMinPeriod() {
    return minPeriod;
}

unsigned long Intervall::getMaxPeriod() {
    return maxPeriod;
}