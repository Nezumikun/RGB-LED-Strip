#include "RgbStrip.h"

#ifndef RGB_STRIP_EFFECTS_H
#define RGB_STRIP_EFFECTS_H

typedef bool (*effectFunc) (struct color_HSV *color);

bool effectFade(struct color_HSV *color);

#endif