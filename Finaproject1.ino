#define NOTE_B3  247
#define NOTE_C4  262

#define MINUTE 60000 // for converting milliseconds to a minute
#define SECOND 1000
#define waterpump 8

#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h> // using this library to set up the rx tx pins


unsigned long seconds = 0;
unsigned long prevM = 0;
const unsigned long interval = 1000;

int sensorM = A0;
const byte rxPin = 3;
const byte txPin = 4;
const byte rx1pin = 11;
const byte tx1pin = 12;
const int pir =  2;
int motion;
int prevMotion = LOW;
//SoftwareSerial mySerial (rxPin, txPin);

SoftwareSerial twoSerial(rx1pin,tx1pin);
unsigned long prevWatertime = 0;
unsigned long currWatertime = 0;

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
unsigned long psMillis = 0;
int timedelay = 500; // This the interval for which the photoresistorshould read the value
unsigned long p = 0;
// The below sets up the lcd screen and sets the cursor to 0,0 and thephoto resistor
void setup() {
  // lcd.init();
  // lcd.backlight();
  // lcd.setCursor(0,0);
  leds.begin();
  clearLEDs();
  Serial1.begin(9600);
  Serial.begin(9600);
  //mySerial.begin(9600);
  pinMode(photoPin,INPUT);
  pinMode(pir, INPUT);
  twoSerial.begin(9600);
  pinMode(waterpump, OUTPUT);
  digitalWrite(waterpump, LOW);

}

void loop() {
  unsigned long currentM = millis();
  //Serial.println("hello");
  if((currentM - prevM) >= 1000){
    prevM = currentM;
    // int output = sensorRead();
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
  //Serial.println("HELLLL");
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
  //Serial.println("hit");
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= timedelay){
    // lcd.clear(); // This clears the lcd display everytime before itdisplays the values
    // lcd.setCursor(0,0);
    int light = analogRead(photoPin);
    Serial.println(light);
    previousMillis = currentMillis;
    // The below if statements print the 5 predefined values on thelcd's based on the value of the photo resistor
    Serial.println("its in here!");
    if(light < 600){
      Serial.println("g");
      Serial1.write('g');
    }
    else{
      Serial.println("n");
      Serial1.write('n');
    }
    if(Serial1.available()){
      char serRead = Serial1.read();
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
    // The below 2 lines prints milliseconds in the second row of the lcd
    // lcd.setCursor(0,1);
    // lcd.print(currentMillis);
  }
  unsigned long csMillis = millis();
  if((csMillis - psMillis) >= 250){
    psMillis = csMillis;
    motion = digitalRead(pir);
    if(motion != prevMotion){
        Serial.print("motion: ");
        Serial.println(motion);
        prevMotion = motion;
        Serial.println("I am working\n");
        if(motion == HIGH){
          for (int thisNote = 0; thisNote < 1; thisNote++) {
            int noteDuration = 500 / noteDurations[thisNote];
            tone(speakerPin, melody[thisNote], noteDuration);
          }
        }
      }else{
        Serial.println("NOPE\n");
        noTone(speakerPin);
      }
  }
}

void clearLEDs(){
  for(int i = 0; i < 30; i++){
    leds.setPixelColor(i,0);
    leds.show();
  }
}
