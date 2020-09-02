#include "RgbStrip.h"

#ifndef RGB_STRIP_EFFECTS_H
#define RGB_STRIP_EFFECTS_H

#define debugln(x)   Serial.print(millis()); Serial.print(" "); Serial.println(x);
#define debug(x)   Serial.print(millis()); Serial.print(" "); Serial.print(x); Serial.print(" ");

typedef bool (*effectFunc) (struct color_HSV *color);

struct effectInfo {
  effectFunc func;
  char times;
};

bool effectBlink(struct color_HSV *color);
bool effectRainbow(struct color_HSV *color);
bool effectBlinkRandom(struct color_HSV *color);

#endif