#include "effects.h"

#define FADE_STEP 2

bool effectBlink(struct color_HSV *color) {
  static unsigned char step = 0;
  static unsigned int hue = 0;
  static int brightness = 0;
  bool res = false;
  if (step == 0) {
    if (brightness == 0) {
      debug("Start blink fade in. Hue = ");
      Serial.println(hue);
    }
    brightness += FADE_STEP;
    if (brightness >= 100) {
      step = 1;
      brightness = 100;
    }
  }
  else if (step == 1) {
    if (brightness >= 100) {
      debugln("Start blink fade out");
    }
    brightness -= FADE_STEP;
    if (brightness <= 0) {
      step = 0;
      brightness = 0;
      hue = (hue + 60) % 360;
      if (hue == 0) {
        res = true;
      }
    }
  }
  color->Hue = hue;
  color->Saturation = 100;
  color->Value = brightness;
  return res;
}

bool effectRainbow(struct color_HSV *color) {
  static unsigned int hue = 0;
  bool res = false;
  if (hue == 0) {
    debugln("Start rainbow");
  }
  if (++hue >= 360) {
    hue = 0;
    res = true;
  }
  color->Hue = hue;
  color->Saturation = 100;
  color->Value = 100;
  return res;
}

bool effectBlinkRandom(struct color_HSV *color) {
  static unsigned char step = 0;
  static unsigned int hue = 0;
  static int brightness = 0;
  bool res = false;
  if (step == 0) {
    if (brightness == 0) {
      hue = (hue + random(330)) % 360;
      debug("Start blink fade in. Random hue = ");
      Serial.println(hue);
    }
    brightness += FADE_STEP;
    if (brightness >= 100) {
      step = 1;
      brightness = 100;
    }
  }
  else if (step == 1) {
    if (brightness >= 100) {
      debugln("Start random blink fade out");
    }
    brightness -= FADE_STEP;
    if (brightness <= 0) {
      step = 0;
      brightness = 0;
      res = true;
    }
  }
  color->Hue = hue;
  color->Saturation = 100;
  color->Value = brightness;
  return res;
}
