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

//!
//! @brief Construct a new Intervall:: Intervall object default intervall length
//!
//!
Intervall::Intervall() {
    timeStamp = 0;
    // assume a default of 100ms
    setPeriod(100);

#ifndef WITHOUT_INTERVALL_STATS
    resetStatistics();
#endif
}

//!
//! @brief Construct a new Intervall:: Intervall object
//!
//! @param newPeriod the new period length for the interval
//!
Intervall::Intervall(Period_t newPeriod) : Intervall() {
    setPeriod(newPeriod);
}

//!
//! @brief set the period length
//!
//! @param newPeriod period length in milliseconds
//!
void Intervall::setPeriod(Period_t newPeriod) {
    period = newPeriod;
}

//!
//! @brief initialize an intervall.
//!
//! Call this function at the start of a sequence of actions, which should be called in a certain intervall
//!
void Intervall::begin(void) {
    timeStamp = millis();
}

//!
//! @brief check if ccurent period is over
//!
//! @return true if current time >= planned time
//! @return false if current time < planned time
//!
bool Intervall::isPeriodOver(void) {
    if (timeStamp == 0)
        return true;
    else
        return millis() - timeStamp >= period;
}

//!
//! @brief wait until the next intervall shall be started
//!
//! This function terminates if the intervall length is reached, an overflow occurs
//! or the userFunc returns true.
//! Ensure that begin() has been called before.
//!
//! @param userFunc if not null and this functions returns true, the intervall is aborted
//! @return Intervall::Result_t result of the intervall
//!
Intervall::Result_t Intervall::wait(bool (*userFunc)(void)) {
    Intervall::Period_t delta  = millis() - timeStamp;
    Result_t            result = Success;

    if (timeStamp == 0) {
        PRINT_ERROR("Intervall not initialized. Call begin() before wait(),", NULL);
        return Intervall::Failure;
    }

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
        while (!isPeriodOver()) {
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

#ifndef WITHOUT_INTERVALL_STATS

//!
//! @brief return the mininum wait period
//!
//! @return Intervall::Period_t
//!
Intervall::Period_t Intervall::getMinPeriod() {
    return minPeriod;
}

//!
//! @brief retuns the maximum wait period
//!
//! @return Intervall::Period_t
//!
Intervall::Period_t Intervall::getMaxPeriod() {
    return maxPeriod;
}

//!
//! @brief return the average wait period
//!
//! @return Intervall::Period_t
//!
Intervall::Period_t Intervall::getAvgPeriod() {
    return sumPeriods / numPeriods;
}

//!
//! @brief reset max/min/average statistics
//!
//!
void Intervall::resetStatistics(void) {
    maxPeriod  = 0;
    minPeriod  = UINT_MAX;

    numPeriods = 0;
    sumPeriods = 0;
}

//!
//! @brief show all statistics
//!
//!
void Intervall::printStatistics(void) {
    PRINT_INFO("Intervall statistics: Period: %u  Min: %u  Max: %u  Average: %u", period, getMinPeriod(),
               getMaxPeriod(), getAvgPeriod());
}

#endif // WITHOUT_INTERVALL_STATS
