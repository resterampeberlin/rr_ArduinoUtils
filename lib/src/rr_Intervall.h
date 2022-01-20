//!
//! @file rr_Intervall.h
//! @author M. Nickels
//! @brief usefull class to work with intervalls/periodic execution
//! @version 0.1
//! @date 2021-12-20
//!
//! @copyright Copyright (c) 2022
//!
//! This file is part of the Application "rr_ArduinoUtils".
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

#pragma once

#include <stddef.h>

class Intervall {

  public:
    //! Available reporting levels
    typedef enum { Success, Abort, Overflow } Result_t;

    //! Constructors
    Intervall();
    Intervall(unsigned long newPeriod);

    void          setPeriod(unsigned long newPeriod);
    void          begin(void);

    Result_t      wait(bool (*userFunc)(void) = NULL);

    unsigned long getMinPeriod();
    unsigned long getMaxPeriod();
    unsigned long getAvgPeriod();

    void resetStatistics(void);

  private:
    unsigned long period;
    unsigned long timeStamp;

    // used for statistics
    unsigned long maxPeriod;
    unsigned long minPeriod;
    unsigned long sumPeriods;
    unsigned long numPeriods;
};