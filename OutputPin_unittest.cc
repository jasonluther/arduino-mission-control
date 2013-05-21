#include "OutputPin.h"
#include "Arduino.h"
#include "gtest/gtest.h"

TEST(OutputPinTest, OutputPinInterface) {
  OutputPin analog_pin_two(A2); // "Output Pin A2"
  OutputPin digital_pin_three(3); // "Output Pin 3 (PWM)"
  
  analog_pin_two.setup();
  digital_pin_three.setup();

  EXPECT_EQ(OUTPUT, get_pinmode_for_test(A2)) << "A2 should be in output mode";
  EXPECT_EQ(OUTPUT, get_pinmode_for_test(3)) << "3 should be in output mode";

  analog_pin_two.set_high();
  digital_pin_three.set_pwm(99);

  EXPECT_EQ(HIGH, digitalRead(A2)) << "A2 should be HIGH";
  EXPECT_EQ(99, analogRead(3)) << "2 should be PWM 99";

  analog_pin_two.set_low();
  digital_pin_three.set_pwm(1);

  EXPECT_EQ(LOW, digitalRead(A2)) << "A2 should be LOW";
  EXPECT_EQ(1, analogRead(3)) << "2 should be PWM 1";
}


