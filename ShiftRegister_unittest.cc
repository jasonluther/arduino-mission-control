#include "OutputPin.h"
#include "ShiftRegister.h"
#include "Arduino.h"
#include "gtest/gtest.h"

TEST(ShiftRegister, Interface) {

  OutputPin serial(1);
  OutputPin rck(2);
  OutputPin srck(3);
  ShiftRegister reg(&serial, &srck, &rck);

  for (int i = 0; i < 4; i++) {
    reg.set_byte(i, 0xff);
  }
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(0xff, reg.test_get_contents(i)) << "all 1's";
  }

  reg.set_byte(2, 0x00);
  reg.set_byte(3, 0x00);
  EXPECT_EQ(0xff, reg.test_get_contents(0)) << "all 1's in first byte";
  EXPECT_EQ(0xff, reg.test_get_contents(1)) << "all 1's in second byte";
  EXPECT_EQ(0, reg.test_get_contents(2)) << "all 0's in third byte";
  EXPECT_EQ(0, reg.test_get_contents(3)) << "all 0's in fourth byte";

  reg.set_byte(1, 0x45);
  //expected_contents = (uint32_t)0xff450000;
  EXPECT_EQ(0xff, reg.test_get_contents(0)) << "still all 1's in first byte";
  EXPECT_EQ(0x45, reg.test_get_contents(1)) << "new value in second byte";
  EXPECT_EQ(0, reg.test_get_contents(2)) << "still all 0's in third byte";
  EXPECT_EQ(0, reg.test_get_contents(3)) << "all 0's in fourth byte";

  reg.set_bit(3, 7, 1);
  //expected_contents = (uint32_t)0xff450001;
  EXPECT_EQ(0xff, reg.test_get_contents(0)) << "even still all 1's in first byte";
  EXPECT_EQ(0x45, reg.test_get_contents(1)) << "same value in second byte";
  EXPECT_EQ(0, reg.test_get_contents(2)) << "even still all 0's in third byte";
  EXPECT_EQ(1, reg.test_get_contents(3)) << "new value in fourth byte";

  reg.set_bit(0, 7, 0);
  //expected_contents = (uint32_t)0xfe450001;
  EXPECT_EQ(0xfe, reg.test_get_contents(0)) << "new value in first byte";
}

TEST(ShiftRegister, SetBit) {

  OutputPin serial(1);
  OutputPin rck(2);
  OutputPin srck(3);
  ShiftRegister reg(&serial, &srck, &rck);

  reg.set_byte(0, 0x00);
  reg.set_bit(0, 0, 1);
  EXPECT_EQ(0x80, reg.test_get_contents(0)) << "new value in first byte";
}


