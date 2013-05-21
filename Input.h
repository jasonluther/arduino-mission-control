#ifndef __INPUT_H
#define __INPUT_H

#include "stdlib.h"

class Input {
public:
  Input(int pin, const char *name);
  ~Input();
  virtual void read_and_set_value(void) { exit(0); };
  virtual void setup(void) { return; };
  int set_value(int new_value);
  int set_changed(int changed);
  int value(void);
  int changed(void);
  int pin(void);
  const char *name(void);
private:
  int _value;
  int _changed;
  const char *_name;
  int _pin;
};

#endif