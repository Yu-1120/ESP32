#include <Arduino.h>

void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // turn the LED on (HIGH is the voltage level)
    delay(1000);                     // wait for a second
}