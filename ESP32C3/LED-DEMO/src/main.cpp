#include <Arduino.h>
//***************************************************************/
//
//           -------------------------------------------
//           board: ESP32C3 Dev Module
//           Flash Mode: "DIO"
//           -------------------------------------------
//
//***************************************************************/

#define LED_D4 12
#define LED_D5 13

void setup() {

    Serial.begin(115200);
    pinMode(LED_D4, OUTPUT);
    pinMode(LED_D5, OUTPUT);
}

void loop() {

    Serial.println("Hello world!");

    digitalWrite(LED_D5, !digitalRead(LED_D5)); //点亮
    delay(100);
    digitalWrite(LED_D4, !digitalRead(LED_D4));


}