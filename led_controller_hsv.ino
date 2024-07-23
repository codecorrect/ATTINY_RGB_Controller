#include <FastLED.h>
#include <SoftPWM.h>
#define RED_PIN 5 // PB0, hardware PWM
#define GREEN_PIN 7 // PB1, hardware PWM
#define BLUE_PIN 9 //PB2, software PWM

#define NUM_LEDS 1  //num of LEDS (1 for the RGB strip)

CRGB leds[NUM_LEDS];  //define array to hold LED data
int hue = 170;
//CRGB colors = CRGB(20, 0, 20);
int DURATION = 1000; //how long leds stay on before fading out
int FADE_TIME = 14;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // init software pwm on BLUE_PIN
  SoftPWMBegin();
  SoftPWMSet(GREEN_PIN, 0);

  //init FastLED w dummy data pin
  FastLED.addLeds<NEOPIXEL,6>(leds, NUM_LEDS);
}

void loop() {
  Serial.begin(9600);

  for (int i = 0; i <= 255; i++) {
    fadeIn(i);
    delay(DURATION);
    Serial.println("HSV Value: " + String(i));
  }
  
  //fadeOut(hue);
  //delay(DURATION);

}

void fadeIn(int hue) {
  //fade in
  for (int brightness = 0; brightness <= 255; brightness++) {
    leds[0] = CHSV(hue, 255, brightness);
    //leds[0].fadeLightBy(255 - brightness);
    applyColor();
    delay(FADE_TIME);
  }
}

void fadeOut(int hue) {
  //fade out
  for (int brightness = 255; brightness >= 0; brightness--) {
    leds[0] = CHSV(hue, 255, brightness);
    //leds[0].fadeLightBy(255 - brightness);
    applyColor();
    delay(FADE_TIME);
  }
}

void applyColor() {
  //extract RGB values
  int redBrightness = leds[0].r;
  int greenBrightness = leds[0].g;
  int blueBrightness = leds[0].b;

  //apply brightness value to leds
  analogWrite(RED_PIN, redBrightness);
  SoftPWMSet(GREEN_PIN, greenBrightness);
  analogWrite(BLUE_PIN, blueBrightness);
}

