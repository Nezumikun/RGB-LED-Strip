#include "RgbStrip.h"

#ifndef RGB_STRIP_EFFECTS_H
#define RGB_STRIP_EFFECTS_H

typedef bool (*effectFunc) (struct color_HSV *color);

struct effectInfo {
  effectFunc func;
  unsigned char times;
};

bool effectBlink(struct color_HSV *color);
bool effectRainbow(struct color_HSV *color);

#endif