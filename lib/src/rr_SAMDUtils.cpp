//!
//! @file rr_SAMDUtils.cpp
//! @author M. Nickels
//! @brief low level routines for Arduino development on SAMD platform
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

//! own includes
#include "rr_SAMDUtils.h"

#ifdef ARDUINO_ARCH_SAMD

void SAMDsetPinFunction(unsigned pin, uint8_t function) {
    // Enable the port multiplexer
    PORT->Group[g_APinDescription[pin].ulPort].PINCFG[g_APinDescription[pin].ulPin].bit.PMUXEN = 1;

    // Connect the pin to the port function
    PORT->Group[g_APinDescription[pin].ulPort].PMUX[g_APinDescription[pin].ulPin >> 1].reg |= function;
}

void SAMDsetWaveGen(Tcc* timer, uint32_t wave, uint32_t overflow) {
    // Set wave generation, frequency and pulse lengths
    timer->WAVE.reg |= wave;

    while (timer->SYNCBUSY.bit.WAVE)
        ;

    timer->PER.reg = overflow - 1;
    while (timer->SYNCBUSY.bit.PER)
        ;
}

void SAMDsetCC(Tcc* timer, unsigned channel, uint32_t value) {
    timer->CC[channel].reg = value;
    while (timer->SYNCBUSY.bit.CC0)
        ;
}

void SAMDenableTCC(Tcc* timer, uint32_t prescaler) {
    timer->CTRLA.reg |= prescaler; // Set prescaler
    timer->CTRLA.bit.ENABLE = 1;   // Enable output
    while (timer->SYNCBUSY.bit.ENABLE)
        ;
}

void SAMDretrigger(Tcc* timer) {
    if (timer->STATUS.bit.STOP) // Check if the previous pulse is complete
    {
        timer->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER; // Retrigger the timer's One/Multi-Shot pulse
        while (timer->SYNCBUSY.bit.CTRLB)
            ;
    }
}

#endif