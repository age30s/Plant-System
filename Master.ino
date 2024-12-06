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


#define NOTE_B3  247
#define NOTE_C4  262

#define MINUTE 60000 // for converting milliseconds to a minute
#define SECOND 1000
#define waterpump 8

#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h> // using this library to set up the rx tx pins
#include <Wire.h>


unsigned long seconds = 0;
unsigned long prevM = 0;
const unsigned long interval = 1000;

int sensorM = A0;

const int pir =  2;
int motion;

unsigned long prevWatertime = 0;
unsigned long currWatertime = 0;
const byte rx1pin = 11;
const byte tx1pin = 12;

SoftwareSerial twoSerial(rx1pin,tx1pin);

#define LED_COUNT 10
#define Pin 7
int lastPirVal = LOW;
unsigned long myTime;          // number of milliseconds passed sincethe Arduino started running the code itself
char printBuffer[128];
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, Pin, NEO_GRB +
NEO_KHZ800);


const int speakerPin = 13;

// notes in the melody:
int melody[] = {
  NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int R = 255;
int G = 255;
int B = 255;
int brightness = 32;

int photoPin = A1; // This is the pin that resistor is connected in the arduino
unsigned long previousMillis = 0;
int timedelay = 500; // This the interval for which the photoresistorshould read the value
unsigned long p = 0;
// The below sets up the lcd screen and sets the cursor to 0,0 and thephoto resistor
void setup() {
 
  leds.begin();
  clearLEDs();
  Serial.begin(9600);
  pinMode(photoPin,INPUT);
  pinMode(pir, INPUT);
  pinMode(waterpump, OUTPUT);
  Wire.begin();
  twoSerial.begin(9600);
  digitalWrite(waterpump, LOW);

}

void loop() {
  unsigned long currentM = millis();
  if((currentM - prevM) >= 1000){
    // writing to slave 1
    prevM = currentM;
    int light = analogRead(photoPin);
    Wire.beginTransmission(0x10);
    //Serial.println(light);
    if(light < 600){
      //Serial.println("g");
      Wire.write('g');
    }
    else{
      //Serial.println("n");
      Wire.write('n');
    }
    Wire.endTransmission();
    byte error = Wire.endTransmission();
    if (error) {
      Serial.print("Error writing to slave: ");
      Serial.println(error);
    }
    // writing to slave 2

    int currSM = analogRead(sensorM);
    int waterlvl = map(currSM, 0, 1023, 255, 0);
    Serial.println(waterlvl);
    char sendingMsg = 'p';
    if(waterlvl < 100){
      sendingMsg = 'l';
    }
    else{
      sendingMsg = 'h';
    }
    Serial.println(sendingMsg);
    Serial.println("????");
    twoSerial.write(sendingMsg); // sending message two third arduinoof moisture level
    Serial.println("....");
    
  }
  if(twoSerial.available()){
    Serial.print("running here\n");
    char recieving = twoSerial.read();
    Serial.println(recieving);
    if(recieving == 'l'){
      currWatertime = millis();
      if((currWatertime - prevWatertime) >= 1000){
        Serial.println("here");
        prevWatertime = currWatertime;
        digitalWrite(waterpump, HIGH);  // Turn on water pump
      }
    }
    else if(recieving == 'h'){
      digitalWrite(waterpump, LOW);
    }
  }
}

void clearLEDs(){
  for(int i = 0; i < 30; i++){
    leds.setPixelColor(i,0);
    leds.show();
  }
}
