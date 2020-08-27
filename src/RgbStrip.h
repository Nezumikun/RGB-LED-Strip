#include <Arduino.h>

#ifndef RGB_STRIP_H
#define RGB_STRIP_H

struct color_RGB {
  byte  valueR;
  byte  valueG;
  byte  valueB;
};

struct color_HSV {
  int   Hue;
  byte  Saturation;
  byte  Value;
};

class RgbStrip {
  private:
    int   ledR;
    int   ledG;
    int   ledB;
    int   powerPin;
    int   maxValue = 100;
    bool  isOff = true;
    struct color_RGB RGB;
    struct color_HSV HSV;
    void printColorRgb();
    void printColorHsv();
    void printHex(int val);

  public:
    RgbStrip(int ledR, int ledG, int ledB, int powerPin);
    void begin();
    void setColorFromRgb(int r, int g, int b);
    void setColorFromHSV(int h, int s, int v);
    struct color_RGB hsv2rgb(int h, int s, int v);
    struct color_HSV rgb2hsv(int r, int g, int b);
    struct color_RGB getRgb();
    struct color_HSV getHsv();
    void setMaxValue(int maxValue);
    int  getMaxValue();
    void setLeds();
    void off();
    void on();
};

#endif
