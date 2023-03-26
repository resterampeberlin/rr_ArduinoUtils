// example for rr_DebugUtils.h
#include <Arduino.h>

#include <Wire.h>

#include "rr_Common.h"
#include "rr_DebugUtils.h"

void setup() {
    // start debugging on serial, 115200 baud
    Debug.beginSerial();

    Wire.begin();

    uint8_t c = scanI2C();

    PRINT_DEBUG("%d devices detected", c);
}

void loop() {
}