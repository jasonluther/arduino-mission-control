#include "Input.h"

Input::Input(int pin, const char *name) {
  _pin = pin;
  _name = name;
}

Input::~Input() {}

int Input::set_value(int new_value) {
  return _value = new_value;
}

int Input::set_changed(int changed) {
  return _changed = changed;
}

int Input::value(void) {
  return _value;
}

int Input::changed(void) {
  return _changed;
}

int Input::pin(void) {
  return _pin;
}

const char *Input::name(void) {
  return _name;
}
