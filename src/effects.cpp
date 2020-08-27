#include "effects.h"

bool effectFade(struct color_HSV *color) {
  static unsigned char step = 0;
  static unsigned int hue = 0;
  static int brightness = 0;
  if (step == 0) {
    brightness += 5;
    if (brightness >= 255) {
      step = 1;
      brightness = 255;
    }
  }
  else if (step == 1) {
    brightness -= 5;
    if (brightness <= 0) {
      step = 0;
      brightness = 0;
      hue = (hue + 120) % 360;
    }
  }
  color->Hue = hue;
  color->Saturation = 100;
  color->Value = brightness;
  return false;
}
