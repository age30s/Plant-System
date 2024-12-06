//Team Number: 3:30-3:55pm

//Name: Kavyasri Challa
//netID: kchal3

//Name: Adithya Prasad
//netID: apras4

//Name: Niharika Patil
//netID: npati2

//Project Name: Automated Plant Care System
//100 Word Abstract: The purpose of this project is to design a plant care system that is easily accessible anywhere, and can be adjustable for any plant. Each arduino will communicate with each other to keep track of three primary tasks: checking the amount of UV light the plant is receiving, tracking the current soil moisture content to see how much water the plant is currently containing, and adjusting the individual needs for the plant, 
//which consists of pouring water and giving light based off of collected 
//readings from the previous arduinos.

#include <Wire.h>
#define waterpump 8

unsigned long seconds = 0;
unsigned long prevM = 0; 
const unsigned long interval = 1000;

int sensorM = A0;
// const byte rxPin = 3;
// const byte txPin = 4;

const byte rx1pin = 9;
const byte tx1pin = 10;

SoftwareSerial twoSerial(rx1pin,tx1pin);
// SoftwareSerial mySerial (rxPin, txPin);

unsigned long prevWatertime = 0;
unsigned long currWatertime = 0;

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  // mySerial.begin(9600);
  twoSerial.begin(9600);
  pinMode(waterpump, OUTPUT);
  digitalWrite(waterpump, LOW);
}

int sensorRead(){
  int currSM = analogRead(sensorM);
  int output = map(currSM, 0, 1023, 255, 0);
  Serial.println("RPERER");
  return output;
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentM = millis();
  
  if((currentM - prevM) >= 1000){
    int output = sensorRead();
    Serial.println(output);
    char sendingMsg;
    if(output >= 100){
      sendingMsg = 'h';
    }
    else{
      sendingMsg = 'l';
    }
    Serial.println("sending.. " + sendingMsg);
    twoSerial.write(sendingMsg); // sending message two third arduino of moisture level
   // Serial.println(sendingMsg);
  }

  // third arduino recieving the status of soil moisture
  if(twoSerial.available()){
    char recieving = twoSerial.read();
    if(recieving == 'l'){
        currWatertime = millis();
        //if((currWatertime - prevWatertime) >= 1000){
          Serial.println("here");
          prevWatertime = currWatertime;
          digitalWrite(waterpump, HIGH);  // Turn on water pump
        //}
        //else {
        //  recieving = 'P';
        //  digitalWrite(waterpump, LOW);
        //}
      }
  }
  else{
    digitalWrite(waterpump, LOW);
  }
 // Serial.println("recieving.. " + recieving);

}
