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
//!      Creative Commons Attribution-ShareAlike 4.0 International License.
//!
//! To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/
//! or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
//!

#include <Arduino.h>
#include <limits.h>

//! own includes
#include "rr_DebugUtils.h"
#include "rr_Intervall.h"

Intervall::Intervall() {
    timeStamp = millis();
    // assume a default og 100ms
    setPeriod(100);

    resetStatistics();
}

Intervall::Intervall(Period_t newPeriod) : Intervall() {
    setPeriod(newPeriod);
}

void Intervall::setPeriod(Period_t newPeriod) {
    period = newPeriod;
}

void Intervall::begin(void) {
    timeStamp = millis();
}

Intervall::Result_t Intervall::wait(bool (*userFunc)(void)) {
    unsigned long delta  = millis() - timeStamp;
    Result_t      result = Success;

#ifndef WITHOUT_INTERVALL_STATS
    // collect statistics
    minPeriod = min(minPeriod, delta);
    maxPeriod = max(maxPeriod, delta);

    // check for overflow
    if (sumPeriods > ULONG_MAX - delta) {
        PRINT_WARNING(F("Average overflow, resetting average"), NULL);

        sumPeriods = getAvgPeriod() + delta;
        numPeriods = 2;
    }
    else {
        sumPeriods += delta;
        numPeriods++;
    }
#endif

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
        PRINT_WARNING("Intervall overflow. Intervall: %u  current: %u", period, delta);

        result = Overflow;
    }

    timeStamp = millis();

    return result;
}

Intervall::Period_t Intervall::getMinPeriod() {
    return minPeriod;
}

Intervall::Period_t Intervall::getMaxPeriod() {
    return maxPeriod;
}

Intervall::Period_t Intervall::getAvgPeriod() {
    return sumPeriods / numPeriods;
}

void Intervall::resetStatistics(void) {
    maxPeriod  = 0;
    minPeriod  = UINT_MAX;

    numPeriods = 0;
    sumPeriods = 0;
}

void Intervall::printStatistics(void) {
    PRINT_INFO("Intervall statistics: Period: %u  Min: %u  Max: %u  Average: %u", period, getMinPeriod(),
               getMaxPeriod(), getAvgPeriod());
}