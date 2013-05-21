#ifndef __INPUT_MANAGER_H
#define __INPUT_MANAGER_H

#include "Input.h"
#include "State.h"

#define NUMINPUTS 12

class InputManager {
public:
  InputManager();
  ~InputManager();
  void add_input(Input *input);
  void add_input_with_state(Input *input, State *s, MCEvent_t low, MCEvent_t high);
  void setup();
  void update();
private:
  Input *_input[NUMINPUTS];
  State *_input_state[NUMINPUTS];
  MCEvent_t _input_event_low[NUMINPUTS];
  MCEvent_t _input_event_high[NUMINPUTS];
  int _inputs;
};

#endif