#ifndef __SHIFTREGISTER_H
#define __SHIFTREGISTER_H
// 4 x TPIC6B595 shift registers chained together 
#define NUM_REGISTERS 4

#include "OutputPin.h"
#include <stdint.h>

class ShiftRegister {
public:
  ShiftRegister(OutputPin *serial_pin, OutputPin *srck_pin, OutputPin *rck_pin);
  void set_byte(int byte, unsigned char new_byte);
  void set_bit(int byte, int offset, bool value);
  void shift_out(void);
  unsigned char test_get_contents(int byte);
private:
  unsigned char contents[NUM_REGISTERS];
  bool changed;
  OutputPin *_SERIAL;
  OutputPin *_SRCK;
  OutputPin *_RCK;
};

#endif