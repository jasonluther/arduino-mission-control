#ifndef __LAUNCHSTATE_H
#define __LAUNCHSTATE_H

#include "State.h"
#include "MCState_t.h"

class LaunchState : public State {
public:
  LaunchState() : State(STATE_COUNTDOWN_DISABLED) {}
  void handle_event(MCEvent_t event);
};

#endif