#include "ShiftRegister.h"
#include "OutputPin.h"
#include "Arduino.h"

ShiftRegister::ShiftRegister(OutputPin *serial_pin, OutputPin *srck_pin, OutputPin *rck_pin) {
  _SERIAL = serial_pin;
  _SRCK = srck_pin;
  _RCK = rck_pin;
  changed = 0;
  for (int i = 0; i < NUM_REGISTERS; i++) {
    contents[i] = 0xff;
  }
}

void ShiftRegister::set_byte(int byte, unsigned char new_byte) {
  contents[byte] = new_byte;
  changed = true;
}

void ShiftRegister::set_bit(int byte, int offset, bool value) {
  unsigned char new_byte = contents[byte];
  unsigned char new_mask = 1 << (7 - offset);
  unsigned char old_mask = ~new_mask;
  new_byte = (new_byte & old_mask) + ((value << (7 - offset)) & new_mask);
  contents[byte] = new_byte;
  changed = true;
}

void ShiftRegister::shift_out(void) {
  if (changed) {
    _RCK->set_low();
    for (int byte = (NUM_REGISTERS - 1); byte >= 0; byte--) {
      for (int bit = 7; bit >= 0; bit--) {
        bool x = (contents[byte] >> (7 - bit)) & 0x1; 
        _SRCK->set_low();
        _SERIAL->set(x);
        _SRCK->set_high();
      }
    }
    _RCK->set_high();
  } else {
  }
  changed = false;
}

unsigned char ShiftRegister::test_get_contents(int byte) {
  return contents[byte];
}

