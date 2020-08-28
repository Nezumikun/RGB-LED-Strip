#include "RgbStrip.h"

RgbStrip::RgbStrip(int ledR, int ledG, int ledB, int powerPin) {
  this->ledR = ledR;
  this->ledG = ledG;
  this->ledB = ledB;
  this->powerPin = powerPin;
}

void RgbStrip::begin() {
  this->RGB.valueR = 255;
  this->RGB.valueG = 255;
  this->RGB.valueB = 255;
  pinMode(this->ledR, OUTPUT);
  pinMode(this->ledG, OUTPUT);
  pinMode(this->ledB, OUTPUT);
  pinMode(this->powerPin, OUTPUT);
  this->setLeds();
  randomSeed(analogRead(0));
  Serial.println(F("RGB Strip initilized"));
}

void RgbStrip::printColorHsv() {
  Serial.print("H = ");
  Serial.print(this->HSV.Hue);
  Serial.print(" S = ");
  Serial.print(this->HSV.Saturation);
  Serial.print(" V = ");
  Serial.print(this->HSV.Value);
  Serial.println();
}

void RgbStrip::printHex(int val) {
  if (val < 0x10)
    Serial.print ("0");
  Serial.print(val, HEX);
}

void inline RgbStrip::printColorRgb() {
    Serial.print ("RGB = 0x");
    printHex (255 - this->RGB.valueR);
    printHex (255 - this->RGB.valueG);
    printHex (255 - this->RGB.valueB);
    Serial.println ();
}
struct color_HSV RgbStrip::rgb2hsv(int r, int g, int b) {
  struct color_HSV temp = { 0, 0, 0 };
  int maxValue = max(max(r, g), b);
  int minValue = min(min(r, g), b);
  if (maxValue == minValue)
    temp.Hue = 0;
  else {
    int delta = maxValue - minValue;
    if ((maxValue == r) && (g >= b))
      temp.Hue = 60 * (g - b) / delta + 0;
    else if ((maxValue == r) && (g < b))
      temp.Hue = 60 * (g - b) / delta + 360;
    else if (maxValue == g)
      temp.Hue = 60 * (b - r) / delta + 120;
    else if (maxValue == b)
      temp.Hue = 60 * (r - g) / delta + 240;
  }
  if (maxValue == 0)
    temp.Saturation = 0;
  else
    temp.Saturation = 100 - 100 * minValue / maxValue;
  temp.Value = 100 * maxValue / 255;
  return temp;
}

void RgbStrip::setColorFromRgb(int r, int g, int b) {
  this->HSV = this->rgb2hsv(r, g, b);
  //this->printColorHsv();
  this->setColorFromHSV(this->HSV.Hue, this->HSV.Saturation, this->HSV.Value);
}

struct color_RGB RgbStrip::hsv2rgb(int h, int s, int v) {
  struct color_RGB temp = { 0, 0, 0 };
  int hi = (int)floor(h/60)%6;
  float vmin = (100 - s) * v / 100;
  float a = (v - vmin) * (h % 60) / 60;
  float vinc = vmin + a;
  float vdec = v - a;
  v *= 2.55;
  vinc *= 2.55;
  vmin *= 2.55;
  vdec *= 2.55;
  if (hi == 0) {
    temp.valueR = v;
    temp.valueG = vinc;
    temp.valueB = vmin;
  }
  else if (hi == 1) {
    temp.valueR = vdec;
    temp.valueG = v;
    temp.valueB = vmin;
  }
  else if (hi == 2) {
    temp.valueR = vmin;
    temp.valueG = v;
    temp.valueB = vinc;
  }
  else if (hi == 3) {
    temp.valueR = vmin;
    temp.valueG = vdec;
    temp.valueB = v;
  }
  else if (hi == 4) {
    temp.valueR = vinc;
    temp.valueG = vmin;
    temp.valueB = v;
  }
  else {
    temp.valueR = v;
    temp.valueG = vmin;
    temp.valueB = vdec;
  }
  return temp;
}

void RgbStrip::setColorFromHSV(int h, int s, int v) {
  this->HSV.Hue = h;
  this->HSV.Saturation = s;
  this->HSV.Value = v;
  v = v * maxValue / 100;
  struct color_RGB temp = this->hsv2rgb(h, s, v);
  this->RGB = { (byte)(255 - temp.valueR), (byte)(255 - temp.valueG), (byte)(255 - temp.valueB) };
  this->setLeds();
}

void RgbStrip::setMaxValue(int maxValue) {
  this->maxValue = maxValue;
  this->setColorFromHSV(this->HSV.Hue, this->HSV.Saturation, this->HSV.Value);
}

void RgbStrip::setLeds() {
  if (this->isOff) {
    analogWrite(this->ledR, 255);
    analogWrite(this->ledG, 255);
    analogWrite(this->ledB, 255);
  }
  else {
    analogWrite(this->ledR, this->RGB.valueR);
    analogWrite(this->ledG, this->RGB.valueG);
    analogWrite(this->ledB, this->RGB.valueB);
  }
  //this->printColorRgb();
  digitalWrite(this->powerPin, HIGH);
}

void RgbStrip::on() {
  this->isOff = false;
  this->setLeds();
}

void RgbStrip::off() {
  this->isOff = true;
  this->setLeds();
}

struct color_RGB RgbStrip::getRgb() {
  return this->hsv2rgb(this->HSV.Hue, this->HSV.Saturation, this->HSV.Value);
}

struct color_HSV RgbStrip::getHsv() {
  return this->HSV;
}

int RgbStrip::getMaxValue() {
  return this->maxValue;
}
