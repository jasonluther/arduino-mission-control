#include "Song.h"
#include "gtest/gtest.h"
#include "mission_control/pitches.h"
#include "Arduino.h"
#include "OutputPin.h"


TEST(SongTest, Play) {
  const int num_notes = 3;
  const int note[num_notes] = { NOTE_G3, NOTE_B3, NOTE_C3 };
  const int duration[num_notes] = { 100, 100, 200 };

  Song s = Song(num_notes, note, duration);
  unsigned long now = 0;

  OutputPin pin(13);

  s.play(&pin, now);
  /* Use digitalRead() as part of our Arduino mock testing interface. */
  EXPECT_EQ(NOTE_G3, digitalRead(13)) << "First note"; 
  s.play(&pin, now + 110);
  EXPECT_EQ(NOTE_B3, digitalRead(13)) << "Second note";
  s.play(&pin, now + 450);
  s.play(&pin, now + 500);
  EXPECT_EQ(0, digitalRead(13)) << "Should be off";
}

