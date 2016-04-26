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
 /* leds1[0] = CRGB::Black;
  leds2[0] = CRGB::Black;
  leds3[0] = CRGB::Black;
  
  FastLED.show();
  for(int i=1; i<NUM_LEDS; i++){
      leds1[i] = CRGB::Red;
      leds2[i] = CRGB::Blue;
      leds3[i] = CRGB::Green;
      FastLED.show();
      delay(10);
      leds1[i] = CRGB::Black;
      leds2[i] = CRGB::Black;
      leds3[i] = CRGB::Black;
      FastLED.show();
      delay(10);
  }*/

  //temperature
  setTemperature(110);
}

void setTemperature(double temp){
  int maxTemp = 110;
  int minTemp = -10;
  int ledsToLight = 0;
  int stepSize = (maxTemp - minTemp) / NUM_LEDS;

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
      temperature[i] = CRGB::Green;
      windSpeed[i] = CRGB::Green;
      forecast[i] = CRGB::Green;
      FastLED.show();
      delay(1);
      temperature[i] = CRGB::Blue;
      windSpeed[i] = CRGB::Blue;
      forecast[i] = CRGB::Blue;
      FastLED.show();
      delay(1);
      temperature[i] = CRGB::Red;
      windSpeed[i] = CRGB::Red;
      forecast[i] = CRGB::Red;
      FastLED.show();
    }
  }

  FastLED.show();
}


