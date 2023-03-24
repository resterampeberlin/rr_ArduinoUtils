//!
//! @file rr_Intervall.h
//! @author M. Nickels
//! @brief usefull class to work with intervalls/periodic execution
//!
//! This file is part of the library "rr_ArduinoUtils".
//!
//!      Creative Commons Attribution-ShareAlike 4.0 International License.
//!
//! To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/
//! or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
//!

#pragma once

#include <stddef.h>

// own includes

//!
//! @brief this class implements the intervall functions
//!
//!
class Intervall {

  public:
    typedef unsigned int Period_t; //!< current period in milliseconds

    //! wait results
    typedef enum { Success, Abort, Overflow, Failure } Result_t;

    //!
    //! @brief Construct a new Intervall:: Intervall object default intervall length
    //!
    Intervall();

    //!
    //! @brief Construct a new Intervall:: Intervall object
    //!
    //! @param newPeriod the new period length for the interval in milliseconds
    //!
    Intervall(Period_t newPeriod);

    //!
    //! @brief set the period length
    //!
    //! @param newPeriod period length in milliseconds
    //!
    void setPeriod(Period_t newPeriod);

    //!
    //! @brief initialize an intervall.
    //!
    //! Call this function at the start of a sequence of actions, which should be called in a certain intervall
    //!
    void begin(void);

    //!
    //! @brief wait until the next intervall shall be started
    //! @details This function terminates if the intervall length is reached, an overflow occurs
    //!          or the userFunc returns true.
    //! @pre Ensure that begin() has been called before.
    //! @param userFunc if not null and this functions returns true, the intervall is aborted
    //! @return result of the intervall
    //!
    Result_t wait(bool (*userFunc)(void) = NULL);

    //!
    //! @brief check if ccurent period is over
    //!
    //! @return true if current time >= planned time
    //! @return false if current time < planned time
    //!
    bool isPeriodOver(void);

#ifndef WITHOUT_INTERVALL_STATS

    //! @name Statistics functions
    //! @note add -DWITHOUT_INTERVALL_STATS to your compiler flags to exclude statistics and save some
    //!       bytes and milliseconds
    //! @{

    //!
    //! @brief return the mininum wait period
    //!
    //! @return Intervall::Period_t
    //!
    Period_t getMinPeriod();

    //!
    //! @brief retuns the maximum wait period
    //!
    //! @return Intervall::Period_t
    //!
    Period_t getMaxPeriod();

    //!
    //! @brief return the average wait period
    //!
    //! @return Intervall::Period_t
    //!
    Period_t getAvgPeriod();

    //!
    //! @brief reset max/min/average statistics
    //!
    void resetStatistics(void);

    //!
    //! @brief show all statistics
    //!
    void printStatistics(void);
    //! @}

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