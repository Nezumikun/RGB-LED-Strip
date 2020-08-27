#include <Arduino.h>
#include "RgbStrip.h"
#include "effects.h"

#define ledR 10
#define ledG 9
#define ledB 6
#define powerPin 8
#define timeQuant 100

RgbStrip strip(ledR, ledG, ledB, powerPin);
struct color_HSV color;
effectFunc effect;
unsigned long prevTime;

void setup() {
  // put your setup code here, to run once:
  prevTime = millis() - timeQuant;
  Serial.begin(115200);
  Serial.println("Hello world!");
  strip.begin();
  strip.setMaxValue(80);
  effect = &effectFade;
  (*effect)(&color);
}

void loop() {
  unsigned long now = millis();
  if (prevTime + timeQuant <= now) {
    Serial.print(now);
    Serial.print(" H = ");
    Serial.print(color.Hue);
    Serial.print(" S = ");
    Serial.print(color.Saturation);
    Serial.print(" V = ");
    Serial.print(color.Value);
    Serial.println();
    strip.setColorFromHSV(color.Hue, color.Saturation, color.Value);
    (*effect)(&color);
    prevTime = now;
  }
}