#include "TimerInput.h"
#include "Input.h"
#include "Arduino.h"
#ifdef TESTING 
#include <iostream>
#endif

TimerInput::TimerInput(const char *name) : Input(100, name) {}

TimerInput::~TimerInput() {}

void TimerInput::read_and_set_value(void) {
    #ifdef TESTING
    //std::cout << "TimerInput::read_and_set_value(void)\n";
    #else 
    //Serial.println("TimerInput::read_and_set_value(void)");
    #endif
  int prev_value = Input::value();
  int cur_value = LOW;
  unsigned long time_now = millis();
  if (!_timer_millis) {
    cur_value = LOW;
  } else if (time_now > _millis_at_start + _timer_millis) {
    #ifdef TESTING
    std::cout << "Timer should go off!\n";
    #else 
    Serial.println("Timer should go off!");
    #endif
    if (prev_value == HIGH) {
      #ifdef TESTING
      std::cout << ("\tTimer was HIGH last time.\n");
      #else 
      Serial.println("\tTimer was HIGH last time.");
      #endif
      // Someone should have noticed that the timer went off.
      cur_value = LOW;
      _millis_at_start = 0;
      _timer_millis = 0;
    } else {
      #ifdef TESTING
      std::cout << "\tFirst time.\n";
      #else 
      Serial.println("\tFirst time.");
      #endif
      cur_value = HIGH;
    }
  }
  int changed = (prev_value != cur_value) ? 1 : 0;
  Input::set_value(cur_value);
  Input::set_changed(changed);
}

void TimerInput::setup(void) {
  #ifdef TESTING
  std::cout << "TimerInput::setup()\n";
  #else 
  Serial.println("TimerInput::setup()");
  #endif
  _millis_at_start = 0;
  _timer_millis = 0;
  Input::set_changed(0);
  Input::set_value(LOW);
}

void TimerInput::set_timer(unsigned long timer_millis) {
  #ifdef TESTING
  #else 
  Serial.println("TimerInput::set_timer()");
  #endif
  _millis_at_start = millis();
  _timer_millis = timer_millis;
  Input::set_changed(0);
  Input::set_value(LOW);
}
