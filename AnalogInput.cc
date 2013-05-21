#include "AnalogInput.h"
#include "Input.h"
#include "Arduino.h"
#include <stdlib.h>

AnalogInput::AnalogInput(int pin, const char *name) : Input(pin, name) { }

AnalogInput::~AnalogInput() {}

void AnalogInput::read_and_set_value(void) {
  int prev_value = Input::value();
  int cur_value = analogRead(Input::pin());
  int changed = (abs(prev_value - cur_value) > 2 ) ? 1 : 0;
  Input::set_value(cur_value);
  Input::set_changed(changed);
}

void AnalogInput::setup(void) {
  pinMode(Input::pin(), INPUT);
}
