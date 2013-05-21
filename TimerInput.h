#ifndef __TIMER_INPUT_H
#define __TIMER_INPUT_H

#include "Input.h"

class TimerInput : public Input {
public:
  TimerInput(const char *name);
  ~TimerInput();
  void read_and_set_value(void);
  void setup(void);
  void set_timer(unsigned long millis);
//private:
  unsigned long _millis_at_start;
  unsigned long _timer_millis;
};

#endif