#include "State.h"
#include "LaunchState.h"
#include "MCEvent_t.h"
#include "MCState_t.h"
#include "gtest/gtest.h"

TEST(StateMachine, Transitions) {

  LaunchState s;
  EXPECT_EQ(STATE_COUNTDOWN_DISABLED, s.get_current_state());

  s.handle_event(EVENT_ARM);
  EXPECT_EQ(STATE_COUNTDOWN_ENABLED, s.get_current_state()) << "ARM when DISABLED goes to ENABLED";
 
  s.set_current_state(STATE_COUNTDOWN_COUNTING);
  s.handle_event(EVENT_ARM);
  EXPECT_EQ(STATE_COUNTDOWN_COUNTING, s.get_current_state()) << "ARM when COUNTING shouldn't happen. If it does, stay in current state.";
 
  s.handle_event(EVENT_RESET_COUNTDOWN);
  EXPECT_EQ(STATE_COUNTDOWN_ENABLED, s.get_current_state()) << "Red button resets the countdown.";
}
