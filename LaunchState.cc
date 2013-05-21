#include "LaunchState.h"
#include "MCState_t.h"
#include "MCEvent_t.h"
#include "Arduino.h"

void LaunchState::handle_event(MCEvent_t event) {
  #ifdef TESTING 
  #else
    Serial.print("LaunchState::handle_event(");
    Serial.print(event);
    Serial.println(")");
  #endif
  switch(_current_state) {
    case STATE_COUNTDOWN_DISABLED:
      switch(event) {
        case EVENT_ARM: 
          transition(STATE_COUNTDOWN_ENABLED);
          break;
        default:
          break;
      }
      break;

    case STATE_COUNTDOWN_ENABLED:
      switch(event) {
        case EVENT_LAUNCH: 
          transition(STATE_LAUNCHING);
          break;
        case EVENT_START_COUNTDOWN: 
          transition(STATE_COUNTDOWN_COUNTING);
          break;
        case EVENT_DISARM: 
          transition(STATE_COUNTDOWN_DISABLED);
          break;
        default:
          break;
      }
      break;

    case STATE_COUNTDOWN_COUNTING:
      switch(event) {
        case EVENT_TIMER_EXPIRED: 
          transition(STATE_COUNTDOWN_AT_ZERO);
          break;
        case EVENT_AT_ZERO: 
          transition(STATE_LAUNCHING);
          break;
        case EVENT_RESET_COUNTDOWN: 
          transition(STATE_COUNTDOWN_ENABLED);
          break;
        case EVENT_DISARM: 
          transition(STATE_COUNTDOWN_DISABLED);
          break;
        case EVENT_LAUNCH: 
          transition(STATE_LAUNCHING);
          break;
        default:
          break;
      }
      break;

    case STATE_COUNTDOWN_AT_ZERO:
      switch(event) {
        case EVENT_RESET_COUNTDOWN: 
          transition(STATE_COUNTDOWN_ENABLED);
          break;
        case EVENT_DISARM: 
          transition(STATE_COUNTDOWN_DISABLED);
          break;
        case EVENT_LAUNCH: 
          transition(STATE_LAUNCHING);
          break;
        default:
          break;
      }
      break;

    case STATE_LAUNCHING:
      switch(event) {
        case EVENT_TIMER_EXPIRED: 
          transition(STATE_COUNTDOWN_ENABLED);
          break;
        case EVENT_DISARM: 
          transition(STATE_COUNTDOWN_DISABLED);
          break;
        case EVENT_RESET_COUNTDOWN: 
          transition(STATE_COUNTDOWN_ENABLED);
          break;
        case EVENT_DONE_LAUNCHING: 
          transition(STATE_COUNTDOWN_ENABLED);
          break;
        default:
          break;
      }
      break;
  }
}