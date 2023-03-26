// example for rr_Intervall.h
#include <Arduino.h>

#include "rr_Intervall.h"

// create an intervall which runs every 500ms
// make it global to access the overall statistics
Intervall intervall(500);

// connect a switch to pin 1, which connects to VCC if pressed
bool callback(void) {
    return digitalRead(1) == HIGH;
}

// setup routine, runs once
void setup() {
    pinMode(1, INPUT);
}

// main function, runs forever
void loop() {
    // start intervall
    intervall.begin();

    // do something which wastes less time than 500ms
    // ...

    // wait until intervall is over
    Intervall::Result_t r = intervall.wait(&callback);

    // this code here will execute 500ms after begin() or
    // if the button has been pressed
    // r will be "aborted" if key on pin 1 has been pressed
}