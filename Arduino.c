#include "Arduino.h"
#include <iostream>

int PINMODE[20];
int PINVALUE[20];
unsigned long _millis = 0;

int get_pinmode_for_test(int pin) {
  std::cout << "get_pinmode_for_test(" << pin << ") = " << PINMODE[pin] << ")\n";
  return PINMODE[pin];
}

void set_pin_for_test(int pin, int value) {
  std::cout << "set_pin_for_test(" << pin << ", " << value << ")\n";
  PINVALUE[pin] = value;
}

void pinMode(int pin, int mode) {
  std::cout << "pinMode(" << pin << ", " << mode << ")\n";
  PINMODE[pin] = mode;
  PINVALUE[pin] = 0;
}

int digitalRead(int pin) {
  std::cout << "digitalRead(" << pin << ") = " << PINVALUE[pin] << "\n";
  return PINVALUE[pin];
}

int analogRead(int pin) {
  std::cout << "analogRead(" << pin << ") = " << PINVALUE[pin + 14] << "\n";
  return PINVALUE[pin + 14];
}

void digitalWrite(int pin, int value) {
  set_pin_for_test(pin, value);
}

void analogWrite(int pin, int value) {
  set_pin_for_test(pin + 14, value);
}

void tone(int pin, int value) {
  set_pin_for_test(pin, value);
}

void tone(int pin, int value, int duration) {
  duration = 0; /* Unused in mock test */
  set_pin_for_test(pin, value);
}

void noTone(int pin) {
  set_pin_for_test(pin, 0);
}

unsigned long millis(void) {
  return _millis;
}

void set_millis_for_test(unsigned long new_millis) {
  _millis = new_millis;
}
