// example for rr_Intervall.h
#include <Arduino.h>

#include "rr_Intervall.h"

// create an intervall which runs every 500ms
// make it global to access the overall statistics
Intervall intervall(500);

// setup routine, runs once
void setup() {
}

// main function, runs forever
void loop() {
    // start intervall
    intervall.begin();

    while (!intervall.isPeriodOver()) {
        // do something which wastes less than 500ms
        // ...
    }

    // this code here will execute 500ms after begin()
}