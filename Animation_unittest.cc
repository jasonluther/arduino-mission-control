#include "Animation.h"
#include "gtest/gtest.h"

#define TEST_NUM_FRAMES 4
const int frames = TEST_NUM_FRAMES;
const int frame[TEST_NUM_FRAMES] = { 'A', 'B', 'C', 'D' };
const int duration[TEST_NUM_FRAMES] = { 10, 100, 20, 20 };

Animation a(frames, frame, duration, true);
Animation b(frames, frame, duration, false);

TEST(AnimationTest, Animation) {
  int t0 = 12345;
  EXPECT_EQ(0, a.get_content()) << "Nothing because we didn't start the animation";
  EXPECT_EQ(0, b.get_content());

  a.animate(t0 + 0); // Start animation
  b.animate(t0 + 0);
  EXPECT_EQ('A', a.get_content()) << "First frame";
  EXPECT_EQ('A', b.get_content());
  EXPECT_EQ(true, a.active());
  EXPECT_EQ(true, b.active());

  a.animate(t0 + 5);
  b.animate(t0 + 5);
  EXPECT_EQ('A', a.get_content()) << "Still on first frame";
  EXPECT_EQ('A', b.get_content());

  a.animate(t0 + 10);
  EXPECT_EQ('B', a.get_content()) << "Should have moved to second frame";

  a.animate(t0 + 20);
  EXPECT_EQ('B', a.get_content()) << "Still on second frame";

  a.animate(t0 + 130);
  EXPECT_EQ('D', a.get_content()) << "Skipped the third frame";

  a.animate(t0 + 140);
  b.animate(t0 + 140);
  EXPECT_EQ('D', a.get_content()) << "Still on last frame";
  EXPECT_EQ('D', b.get_content());

  a.animate(t0 + 150);
  b.animate(t0 + 150);
  EXPECT_EQ('A', a.get_content()) << "Looped";
  EXPECT_EQ(0, b.get_content()) << "Animation should stop";
  EXPECT_EQ(true, a.active());
  EXPECT_EQ(false, b.active());

  a.animate(t0 + 150 + 120);
  EXPECT_EQ('C', a.get_content()) << "Made it to third frame this time";

}

TEST(AnimationTest, HandleMillisWrap) {
// XXX test animation when millis() rolls over
}

TEST(AnimationTest, OneFrameAnimation) {
  int single_frame[1] = { 'J' };
  int single_duration[1] = { 1000 };
  Animation oneframe(1, single_frame, single_duration);

  oneframe.animate(0);
  EXPECT_EQ('J', oneframe.get_content()) << "first frame";

  oneframe.animate(1000);
  EXPECT_EQ('J', oneframe.get_content()) << "same frame";

  oneframe.animate(20000);
  EXPECT_EQ('J', oneframe.get_content()) << "still the same frame";
}


