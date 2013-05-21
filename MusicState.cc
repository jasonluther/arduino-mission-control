#include "MusicState.h"
#include "MCState_t.h"
#include "MCEvent_t.h"
#include "Arduino.h"

void MusicState::handle_event(MCEvent_t event) {
  switch(_current_state) {
    case STATE_MUSIC_OFF:
      switch(event) {
        case EVENT_START_MUSIC: 
          transition(STATE_MUSIC_ON);
          break;
        default:
          break;
      }
      break;

    case STATE_MUSIC_ON:
      switch(event) {
        case EVENT_STOP_MUSIC: 
          transition(STATE_MUSIC_OFF);
          break;
        default:
          break;
      }
      break;
  }
}