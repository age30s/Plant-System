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

#define LED_COUNT 10
#define Pin 7
#define SLAVE_ADDRESS 0x10

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
  //clearLEDs();
  Serial.begin(9600);
  // mySerial.begin(9600);
  pinMode(photoPin,INPUT);
  pinMode(pir, INPUT);
  pinMode(waterpump, OUTPUT);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(event);
  digitalWrite(waterpump, LOW);
}

void loop() {
  //Wire.onReceive(event);
  motion = digitalRead(pir);
  if(motion == HIGH){
    for (int thisNote = 0; thisNote < 2; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(speakerPin, melody[thisNote], noteDuration);
    }
  }else{
    noTone(speakerPin);
  }
}

void event(int bytes){
  if(Wire.available()){
      char serRead = Wire.read();
      Serial.println(serRead);
      Serial.println("..");
      if(serRead == 'g'){
        for(int i = 0; i < LED_COUNT; i++){
          leds.setPixelColor(i,R,G,B);
          leds.setBrightness(brightness);
          leds.show();
        }
      }else if(serRead == 'n'){
        clearLEDs();
      }
    }
}

void clearLEDs(){
  for(int i = 0; i < 30; i++){
    leds.setPixelColor(i,0);
    leds.show();
  }
}
