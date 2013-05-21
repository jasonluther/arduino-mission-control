#include "RadarRGB.h"
#include "OutputPin.h"

/* Adapted from http://www.cs.rit.edu/~ncs/color/t_convert.html */
/* but hue = 0-359, assume S & V are 1. RGB are 0-255. */
void set_rgb_from_hue(OutputPin *redPin, OutputPin *greenPin, OutputPin *bluePin, int hue) {
  int sector;
  int r, g, b;
  float fraction, q, t;
  hue %= 360;
  sector = hue / 60;
  fraction = (hue % 60) / 60.0;
  t = 255 * fraction;
  q = 255 - t;
  switch(sector) {
    case 0:
      r = 255;
      g = t;
      b = 0;
      break;
    case 1:
      r = q;
      g = 255;
      b = 0;
      break;
    case 2:
      r = 0;
      g = 255;
      b = t;
      break;
    case 3:
      r = 0;
      g = q;
      b = 255;
      break;
    case 4:
      r = t;
      g = 0;
      b = 255;
      break;
    case 5:
      r = 255;
      g = 0;
      b = q;
      break;
  }
  redPin->set_pwm(r);
  greenPin->set_pwm(g);
  bluePin->set_pwm(b);
}
