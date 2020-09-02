#include <Arduino.h>
#include "RgbStrip.h"
#include "effects.h"

#define ledR 10
#define ledG 9
#define ledB 6
#define powerPin 8
#define timeQuant 40

RgbStrip strip(ledR, ledG, ledB, powerPin);
struct color_HSV colorHSV;
unsigned long prevTime;
const effectInfo effectList[] = {
  { effectBlink, -2 }, { effectRainbow, -5 }, { effectBlinkRandom, -5 }, { effectRainbow, -5 }
};
unsigned char currentEffect = 0;
unsigned char currentTime = 0;

void inline showCurrentSequence(unsigned long now) {
      Serial.print(now);
      Serial.print(" Seq = ");
      Serial.print(currentEffect);
      Serial.print(" t = ");
      Serial.print(currentTime);
      Serial.println();
}

unsigned char inline getEffectTimes(unsigned char index) {
  return effectList[index].times > 0 ? effectList[index].times : (random(-effectList[index].times) + 1);
}

void setup() {
  // put your setup code here, to run once:
  prevTime = millis() - timeQuant;
  Serial.begin(115200);
  strip.begin();
  strip.setMaxValue(80);
  currentTime = getEffectTimes(currentEffect);
  showCurrentSequence(millis());
  (*(effectList[currentEffect].func))(&colorHSV);
  strip.setColorFromHSV(colorHSV.Hue, colorHSV.Saturation, colorHSV.Value, false);
  strip.on();
}

void loop() {
  unsigned long now = millis();
  if (prevTime + timeQuant <= now) {
    strip.setLeds();
    // unsigned long now2 = micros();
    if ((*(effectList[currentEffect].func))(&colorHSV)) {
      if (--currentTime <= 0) {
        currentEffect++;
        if (currentEffect >= sizeof(effectList)/sizeof(effectInfo)) {
          currentEffect = 0;
        }
        currentTime = getEffectTimes(currentEffect);
      }
      showCurrentSequence(now);
    }
    strip.setColorFromHSV(colorHSV.Hue, colorHSV.Saturation, colorHSV.Value, false);
    prevTime = now;
    // Serial.println(micros() - now2);
  }
}