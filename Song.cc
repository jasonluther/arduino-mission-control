#include "Song.h"
#include "Animation.h"
#include "Arduino.h"
#include "OutputPin.h"

Song::Song(int num_notes, const int note[], const int duration[]) :
  Animation(num_notes, note, duration, false) {
}

void Song::play(OutputPin *pin, unsigned long millis) {
  animate(millis);
  int animation_frame = get_current_frame();
  if (animation_frame != _current_animation_frame) {
    _current_animation_frame = animation_frame;
    if (active()) {
      pin->set_tone(get_content(), get_duration());
    } else {
      pin->no_tone();
    }
  }
}