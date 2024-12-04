// Kavyasri Challa, 653418742, kchal3
// Lab 4 - Analog Input: Photoresistor (LDR – Light Dependent Resistor)
// This code is supposed take the inputs from the photo resistor and assign 5 predefined values(dark, partially dark, medium, fully lit, brightly lit). The predefined values will be displayed on the first row of the lcd based on the value that the photoresistor is reading and the seconds will be displayed on the second row of the lcd.
// I thought that the photoresitor would have a very high value such as 1000 for brightly lit.
// References: : https://www.circuitbasics.com/how-to-usephotoresistors-to-detect-light-on-an-arduino/ - provided in the lab description
// TA Name: Yamaan Nandolia

// #include <LiquidCrystal_I2C.h>
// #include  <Wire.h>
// LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h> // using this library to set up the rx tx pins
const byte rxPin = 3;
const byte txPin = 4;
SoftwareSerial mySerial (rxPin, txPin);
#define LED_COUNT 10
#define Pin 7

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, Pin, NEO_GRB + NEO_KHZ800);

int R = 255;
int G = 255;
int B = 255;
int brightness = 32;

int photoPin = A0; // This is the pin that resistor is connected in the arduino
unsigned long previousMillis = 0; 
int timedelay = 500; // This the interval for which the photoresistor should read the value

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
  }
}

void clearLEDs(){
  for(int i = 0; i < 30; i++){
    leds.setPixelColor(i,0);
    leds.show();
  }
}
