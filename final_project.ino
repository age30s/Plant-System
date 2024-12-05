// Kavyasri Challa, 653418742, kchal3
// Lab 4 - Analog Input: Photoresistor (LDR – Light Dependent Resistor)
// This code is supposed take the inputs from the photo resistor and assign 5 predefined values(dark, partially dark, medium, fully lit, brightly lit). The predefined values will be displayed on the first row of the lcd based on the value that the photoresistor is reading and the seconds will be displayed on the second row of the lcd.
// I thought that the photoresitor would have a very high value such as 1000 for brightly lit.
// References: : https://www.circuitbasics.com/how-to-usephotoresistors-to-detect-light-on-an-arduino/ - provided in the lab description
// TA Name: Yamaan Nandolia

// #include <LiquidCrystal_I2C.h>
// #include  <Wire.h>
// LiquidCrystal_I2C lcd(0x27, 16, 2);
/*
  This code plays a melody on a Audio Module and Speaker module connected to an Arduino Uno board. 
  The melody is played once in the setup() function and consists of eight notes with 
  different durations.
  
  Board: Arduino Uno R4
  Component: Audio Module and Speaker
*/

/*************************************************
 * Public Constants
 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h> // using this library to set up the rx tx pins
const byte rxPin = 3;
const byte txPin = 4;
const int pir =  2;
int motion;
SoftwareSerial mySerial (rxPin, txPin);
#define LED_COUNT 10
#define Pin 7

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, Pin, NEO_GRB + NEO_KHZ800);


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

int photoPin = A0; // This is the pin that resistor is connected in the arduino
unsigned long previousMillis = 0; 
int timedelay = 500; // This the interval for which the photoresistor should read the value
unsigned long p = 0;
// The below sets up the lcd screen and sets the cursor to 0,0 and the photo resistor
void setup() {
  // lcd.init();
  // lcd.backlight();
  // lcd.setCursor(0,0);
  leds.begin();
  clearLEDs();
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(photoPin,INPUT);
  pinMode(pir, INPUT);

}

void loop() {

  // for(int i = 0; i < LED_COUNT; i++){
  //   leds.setPixelColor(i,R,G,B);
  //   leds.setBrightness(brightness);
  //   leds.show();
  // }


  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= timedelay){
    // lcd.clear(); // This clears the lcd display everytime before it displays the values
    // lcd.setCursor(0,0);
    motion = digitalRead(pir);
    int light = analogRead(photoPin);
    Serial.println(light);
    previousMillis = currentMillis;
    // The below if statements print the 5 predefined values on the lcd's based on the value of the photo resistor
    if(light < 600){
      mySerial.write('l');
    }
    else{
      mySerial.write('n');  
    }
    if(mySerial.available()){
      char serRead = mySerial.read(); 
      if(serRead == 'l'){
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
    if(motion == HIGH){
      Serial.println("I am working\n");
      for (int thisNote = 0; thisNote < 2; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(speakerPin, melody[thisNote], noteDuration);
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
