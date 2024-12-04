// Niharika Patil, 659652730, npati2

/* Description - */

// References:

#include <Wire.h>
//#include  <I2CLiquidCrystal.h>

#define waterpump 8
int buttonPin = 5;
int button_state;

int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(waterpump, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(waterpump, LOW);
}

void  loop() {
  int reading = digitalRead(buttonPin);
  //Serial.println(reading);
  if (reading != lastButtonState) { //this will check for if we are using the first button
    //Serial.print("HELLO\n");
    lastDebounceTime = millis(); //reset the debounce timer
  }
  //Serial.print("HELLO IAM AHERE\n");
  if ((millis() - lastDebounceTime) > debounceDelay) { 
    if (reading != button_state){
      button_state = reading;
      if (button_state == HIGH) {
        digitalWrite(waterpump, HIGH);  // Turn on water pump
        //Serial.print("button is high\n");
      }
      else {
        digitalWrite(waterpump, LOW);
        //Serial.print("button is low\n");
      }
    }
  } 
  lastButtonState = reading;
}
