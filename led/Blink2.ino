/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#include "FastLED.h"

#define NUM_LEDS 60
#define DATA_PIN1 53
#define DATA_PIN2 51
#define DATA_PIN3 49
#define CLOCK_PIN 13

CRGB temperature[NUM_LEDS];
CRGB windSpeed[NUM_LEDS];
CRGB forecast[NUM_LEDS];

// function prototypes
void setTemperature(double, CRGB[]);

// the setup function runs once when you press reset or power the board
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN1>(temperature, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN2>(windSpeed, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN3>(forecast, NUM_LEDS);
}

// the loop function runs over and over again forever
void loop() {
  //temperature
  setTemperature(110);
}

void setTemperature(double temp){
  int maxTemp = 110;
  int minTemp = -10;
  int ledsToLight = 0;
  int stepSize = (maxTemp - minTemp) / NUM_LEDS;

  double hotThreshold = 0.75;
  double warmThreshold = 0.5;
  double coolThreshold = 0.25;

  if (temp >= maxTemp) {
    ledsToLight = NUM_LEDS;
  } else if(temp < minTemp) {
    ledsToLight = 0;
  } else {
    ledsToLight = temp / stepSize;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    temperature[i] = CRGB::Black;
    if (i <= ledsToLight) {
      if(i / NUM_LEDS >= hotThreshold){
        temperature[i] = CRGB::Crimson;
      } else if (i/NUM_LEDS >= warmThreshold){
        temperature[i] = CRGB::MediumVioletRed;
      } else if (i/NUM_LEDS >= coolThreshold){
        temperature[i] = CRGB::LightBlue;
      } else {
        temperature[i] = CRGB::MidnightBlue;
      }
    }
  }
  FastLED.show();
}

void setWindSpeed(double wSpeed){
  for(int i=0; i< NUM_LEDS; i++){
    windSpeed[i] = CRGB::LightGoldenrodYellow;
  }
  FastLED.show();

  for(int i=0;i<NUM_LEDS;i++){
    windSpeed[i] = CRGB::MidnightBlue;
    FastLED.show();
    delay((int) 250/wSpeed);
    windSpeed[i] = CRGB::LightGoldenrodYellow;
    FastLED.show();
  }
}


