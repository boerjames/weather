/*
  LED controlling program
  Weather Project
  Embedded Systems  |  Dr. Paul Grabow, S16

  Authors:  James Boer
            Matt Santiago
            Kyle Unruh
*/

//Pull in FastLED library for led addressing and control
#include "FastLED.h"

//Constants
#define NUM_LEDS 60
#define DATA_PIN1 53
#define DATA_PIN2 51
#define DATA_PIN3 49
#define CLOCK_PIN 13

CRGB temperature[NUM_LEDS]; //temperature strip
CRGB windSpeed[NUM_LEDS];   //wind speed strip
CRGB forecast[NUM_LEDS];    //forecast strip

void setup() {
  //Initialization
  FastLED.addLeds<NEOPIXEL, DATA_PIN1>(temperature, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN2>(forecast, NUM_LEDS);
  setSolidColor(-1);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  //Loop through the states of solid colors
  //Show progression along temperature strip
  for (int i = 0; i < 10; i++) {
    setSolidColor(i);
    for (double j = -10; j < 111; j+=0.1) {
      setTemperature(j);
      delay(10);
    }
  }
}


//Lights a section of the led strip proportional to the temperature
//Simulates a mercury thermometer
//As temperature increases, more LEDs are illuminated
void setTemperature(double temp){
  int maxTemp = 110;
  int minTemp = -10;
  int range = maxTemp - minTemp;
  double ledsToLight = 0;
  double stepSize = range / NUM_LEDS;

  double colorStep = 255 / range;
  int red = temp * colorStep;
  int blue = 255 - red;
  CRGB color = CRGB(red, 0, blue);

  if (temp >= maxTemp) {
    ledsToLight = NUM_LEDS;
  } else if(temp < minTemp) {
    ledsToLight = 0;
  } else {
    ledsToLight = temp / stepSize;
    Serial.print(ledsToLight);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    temperature[i] = CRGB::Black;
    if (i <= ledsToLight) {
      temperature[i] = color;
    }
  }
  FastLED.show();
}

//Simulates a wind speed by propogating an LED with
//varying delays
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

//Sets the forecast strip to a single solid color
void setSolidColor(int num){
  for(int i=0; i<NUM_LEDS;i++){
  switch(num){
    case 0:
      forecast[i] = CRGB::Red;
      break;
    case 1:
      forecast[i] = CRGB::Blue;
      break;
    case 2:
      forecast[i] = CRGB::Green;
      break;
    case 3:
      forecast[i] = CRGB::LightGoldenrodYellow;
      break;
    case 4:
      forecast[i] = CRGB::MidnightBlue;
      break;
    case 5:
      forecast[i] = CRGB::MediumVioletRed;
      break;
    case 6:
      forecast[i] = CRGB::LightBlue;
      break;
    case 7:
      forecast[i] = CRGB::Crimson;
      break;
    case 8:
      forecast[i] = CRGB::Purple;
      break;
    case 9:
      forecast[i] = CRGB::Orange;
      break;
    default:
      forecast[i] = CRGB::Black;
      break;
  }
  }
  FastLED.show();
}
