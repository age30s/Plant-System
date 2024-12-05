#include <Wire.h>
#include <SoftwareSerial.h> // using this library to set up the rx tx pins

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
