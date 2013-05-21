#ifndef __STATE_H
#define __STATE_H

#include "MCState_t.h"
#include "MCEvent_t.h"

class State {
public:
  State(MCState_t initial_state);
  virtual void handle_event(MCEvent_t event) { if (event) return; };
  MCState_t get_current_state(void) { return _current_state; }
// for testing:
  void set_current_state(MCState_t new_state) { _current_state = new_state; }

  void transition(MCState_t new_state);
  MCState_t _current_state;
};

#endif