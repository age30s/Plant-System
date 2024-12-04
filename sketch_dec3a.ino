// Niharika Patil, 659652730, npati2

/* Description - */

// References:

#include <Wire.h>
//#include  <I2CLiquidCrystal.h>

#define waterpump 8


void setup() {
    pinMode(waterpump, OUTPUT);
    digitalWrite(waterpump, LOW);

}

void  loop() {
  // if (soilMoisture > 650) {
    digitalWrite(waterpump, HIGH);  // Turn on water pump
  //}
  
}