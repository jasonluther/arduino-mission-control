#include "OutputPin.h"
#include "Arduino.h"

OutputPin::OutputPin(int pin) {
  _pin = pin;
}

OutputPin::~OutputPin() {};

void OutputPin::setup(void) {
  pinMode(_pin, OUTPUT);
};

void OutputPin::set_pwm(int value) {
  analogWrite(_pin, value);
};

void OutputPin::set_high() {
  set(HIGH);
};

void OutputPin::set_low() {
  set(LOW);
};

void OutputPin::set(int value) {
  digitalWrite(_pin, value);
}

void OutputPin::set_tone(int frequency, int duration) {
  tone(_pin, frequency, duration);
}

void OutputPin::set_tone(int frequency) {
  tone(_pin, frequency);
}

void OutputPin::no_tone() {
  noTone(_pin);
}
