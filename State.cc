#include "State.h"
#include "MCState_t.h"
#include "MCEvent_t.h"
#include "Arduino.h"
#ifdef TESTING
#include <iostream>
#endif

State::State(MCState_t initial_state) {
  _current_state = initial_state;
}

void State::transition(MCState_t new_state) {
#ifdef TESTING
  std::cout << "Transition from " << _current_state << " to " << new_state << "\n";
#else
  Serial.print("Transition from ");
  Serial.print(_current_state);
  Serial.print(" to ");
  Serial.println(new_state);
#endif
  _current_state = new_state;
}