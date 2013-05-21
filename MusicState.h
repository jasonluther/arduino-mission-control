#ifndef __MUSICSTATE_H
#define __MUSICSTATE_H

#include "State.h"
#include "MCState_t.h"

class MusicState : public State {
public:
  MusicState() : State(STATE_MUSIC_OFF) {}
  void handle_event(MCEvent_t event);
};

#endif