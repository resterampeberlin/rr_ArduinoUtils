// example for rr_DebugUtils.h
#include <Arduino.h>

#include "rr_DebugUtils.h"

void setup() {
    // start debugging on serial, 115200 baud
    Debug.beginSerial();

    // set a tab on column 30 to increase monitor output formatting
    Debug.setTab(30);
    PRINT_BUILD();

    // print some colored messages
    PRINT_VERBOSE("Verbose", NULL);
    PRINT_DEBUG("Debug", NULL);
    PRINT_INFO("Info", NULL);
    PRINT_WARNING("Warning", NULL);
    PRINT_ERROR("Error", NULL);

    // print formatted data
    PRINT_DEBUG("An integer: %d  unsigned: %u  float: %f   string: %s", -1234, 2345, 5678.9, "a string");
}

void loop() {
}