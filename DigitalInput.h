#ifndef __DIGITAL_INPUT_H
#define __DIGITAL_INPUT_H

#include "Input.h"

class DigitalInput : public Input {
public:
  DigitalInput(int pin, const char *name);
  ~DigitalInput();
  void read_and_set_value(void);
  void setup(void);
};

#endif