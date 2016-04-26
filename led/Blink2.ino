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

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

// the setup function runs once when you press reset or power the board
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN1>(leds1, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN2>(leds2, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN3>(leds3, NUM_LEDS);
}

// the loop function runs over and over again forever
void loop() {
  leds1[0] = CRGB::Black;
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
  }
  
}
