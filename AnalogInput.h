#ifndef __ANALOG_INPUT_H
#define __ANALOG_INPUT_H

#include "Input.h"

class AnalogInput : public Input {
public:
  AnalogInput(int pin, const char *name);
  ~AnalogInput();
  void read_and_set_value(void);
  void setup(void);
};

#endif