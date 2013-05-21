#include "Input.h"
#include "InputManager.h"
#include "AnalogInput.h"
#include "DigitalInput.h"
#include "TimerInput.h"
#include "Arduino.h"
#include "gtest/gtest.h"
#include "MCEvent_t.h"
#include "MCState_t.h"
#include "State.h"
#include "LaunchState.h"

TEST(InputTest, DigitalInput) {
  DigitalInput input3(3, "Input 3");
  pinMode(3, INPUT);
  set_pin_for_test(3, HIGH);
  
  input3.read_and_set_value();
  EXPECT_EQ(HIGH, input3.value()) << "read the value";

  set_pin_for_test(3, HIGH);
  input3.read_and_set_value();
  EXPECT_EQ(HIGH, input3.value()) << "value should still be the same";
  EXPECT_EQ(0, input3.changed()) << "no change";

  set_pin_for_test(3, LOW);
  input3.read_and_set_value();
  EXPECT_EQ(LOW, input3.value()) << "now it's LOW";
  EXPECT_EQ(1, input3.changed()) << "yes change";
}

TEST(InputTest, AnalogInput) {
  AnalogInput input2(2, "Input A2");
  pinMode(A2, INPUT);
  set_pin_for_test(A2, 128);
  
  input2.read_and_set_value();
  EXPECT_EQ(128, input2.value()) << "read the value";

  set_pin_for_test(A2, 128);
  input2.read_and_set_value();
  EXPECT_EQ(128, input2.value()) << "value should still be the same";
  EXPECT_EQ(0, input2.changed()) << "no change";

  set_pin_for_test(A2, 256);
  input2.read_and_set_value();
  EXPECT_EQ(256, input2.value()) << "now it's 256";
  EXPECT_EQ(1, input2.changed()) << "yes change";
}

TEST(InputTest, AnalogInputAsDigital) {
  DigitalInput inputA2(A2, "Input A2");
  pinMode(A2, INPUT);
  set_pin_for_test(A2, HIGH);
  inputA2.read_and_set_value();
  EXPECT_EQ(HIGH, inputA2.value()) << "HIGH";

  set_pin_for_test(A2, LOW);
  inputA2.read_and_set_value();
  EXPECT_EQ(LOW, inputA2.value()) << "LOW";
}

TEST(InputManager, TestInputManager) {
  InputManager m;

  DigitalInput d2 = DigitalInput(A2, "Yellow Button"); 
  m.add_input(&d2);
  DigitalInput d3 = DigitalInput(A3, "Red Button"); 
  m.add_input(&d3);
  DigitalInput d4 = DigitalInput(A4, "Green Button"); 
  m.add_input(&d4);
  DigitalInput d6 = DigitalInput(11, "Arm Switch"); 
  m.add_input(&d6);
  DigitalInput d7 = DigitalInput(12, "Right Switch"); 
  m.add_input(&d7);
  DigitalInput d8 = DigitalInput(2, "Left Switch"); 
  m.add_input(&d8);
  AnalogInput a1 = AnalogInput(0, "Black Knob"); 
  m.add_input(&a1);
  AnalogInput a2 = AnalogInput(5, "Silver Knob"); 
  m.add_input(&a2);

  m.setup();
  m.update();

  set_pin_for_test(A0, 1234);
  set_pin_for_test(3, LOW);
  m.update();
}

TEST(InputManager, StateManagement) {
  InputManager m;
  LaunchState launchState;

  DigitalInput d1 = DigitalInput(A1, "Launch Button"); 
  m.add_input_with_state(&d1, &launchState, EVENT_LAUNCH, EVENT_NOOP);

  DigitalInput d5 = DigitalInput(3, "Key Switch"); 
  m.add_input_with_state(&d5, &launchState, EVENT_DISARM, EVENT_ARM);

  m.setup();
  set_pin_for_test(A1, HIGH);
  set_pin_for_test(3, HIGH);
  m.update();

  set_pin_for_test(A1, LOW);
  m.update();
  EXPECT_EQ(STATE_LAUNCHING, launchState.get_current_state()) << "Launch button";

  set_pin_for_test(3, LOW);
  m.update();
  EXPECT_EQ(STATE_COUNTDOWN_DISABLED, launchState.get_current_state()) << "Switch off";

  set_pin_for_test(3, HIGH);
  m.update();
  EXPECT_EQ(STATE_COUNTDOWN_ENABLED, launchState.get_current_state()) << "Switch on";
}

TEST(InputManager, Timer) {
  InputManager m;
  LaunchState launchState;
  set_millis_for_test(0);
  
  TimerInput t = TimerInput("A Timer");
  m.add_input_with_state(&t, &launchState, EVENT_NOOP, EVENT_TIMER_EXPIRED);

  launchState.set_current_state(STATE_LAUNCHING);
  m.setup();
  m.update();
  EXPECT_EQ(STATE_LAUNCHING, launchState.get_current_state());

  t.set_timer(100);
  set_millis_for_test(99);
  m.update();
  EXPECT_EQ(STATE_LAUNCHING, launchState.get_current_state());

  set_millis_for_test(101);
  m.update();
  EXPECT_EQ(STATE_COUNTDOWN_ENABLED, launchState.get_current_state());

  // Now that the timer has been seen to go off, it should be LOW.
  m.update();
  EXPECT_EQ(LOW, t.value());
}

