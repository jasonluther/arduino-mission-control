#ifndef __OUTPUTPIN_H
#define __OUTPUTPIN_H

class OutputPin {
public:
  OutputPin(int pin);
  ~OutputPin();
  void setup(void);
  void set_high();
  void set_low();
  void set(int value);
  void set_pwm(int value);
  void set_tone(int frequency, int duration);
  void set_tone(int frequency);
  void no_tone(void);
  int pin(void) { return _pin; };
private:
  int _pin;
};

#endif
