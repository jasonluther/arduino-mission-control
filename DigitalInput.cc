#include "DigitalInput.h"
#include "Input.h"
#include "Arduino.h"

DigitalInput::DigitalInput(int pin, const char *name) : Input(pin, name) { }

DigitalInput::~DigitalInput() {}

void DigitalInput::read_and_set_value(void) {
  int prev_value = Input::value();
  int cur_value = digitalRead(Input::pin());
  int changed = (prev_value != cur_value) ? 1 : 0;
  Input::set_value(cur_value);
  Input::set_changed(changed);
}

void DigitalInput::setup(void) {
  pinMode(Input::pin(), INPUT_PULLUP);
}
