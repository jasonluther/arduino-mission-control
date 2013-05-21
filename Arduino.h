#ifndef __ARDUINO_H
#define __ARDUINO_H

#define TESTING

extern int PINMODE[20];
extern int PINVALUE[20];

#define false 0
#define true 1
#define HIGH 1
#define LOW 0
#define INPUT 0
#define INPUT_PULLUP 1
#define OUTPUT 2

#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19

void pinMode(int pin, int mode);
int digitalRead(int pin);
int analogRead(int pin);
void digitalWrite(int pin, int value);
void analogWrite(int pin, int value);

void set_pin_for_test(int pin, int value);
int get_pinmode_for_test(int pin);

void tone(int pin, int value, int duration);
void tone(int pin, int value);
void noTone(int pin);

unsigned long millis(void);
void set_millis_for_test(unsigned long new_millis);

#endif