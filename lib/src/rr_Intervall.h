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
//!      Creative Commons Attribution-ShareAlike 4.0 International License.
//!
//! To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/
//! or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
//!

#pragma once

#include <stddef.h>

class Intervall {

  public:
    typedef unsigned int Period_t;

    //! wait results
    typedef enum { Success, Abort, Overflow, Failure } Result_t;

    //! Constructors
    Intervall();
    Intervall(Period_t newPeriod);

    void     setPeriod(Period_t newPeriod);
    void     begin(void);

    Result_t wait(bool (*userFunc)(void) = NULL);

    bool     isPeriodOver(void);

//! add -DWITHOUT_INTERVALL_STATS to your compiler flags to exclude statistics and save some
//! bytes and milliseconds
#ifndef WITHOUT_INTERVALL_STATS
    Period_t getMinPeriod();
    Period_t getMaxPeriod();
    Period_t getAvgPeriod();

    void     resetStatistics(void);
    void     printStatistics(void);
#endif

  private:
    Period_t      period;
    unsigned long timeStamp;

#ifndef WITHOUT_INTERVALL_STATS
    // used for statistics
    Period_t      maxPeriod;
    Period_t      minPeriod;
    unsigned      sumPeriods;
    unsigned long numPeriods;
#endif
};