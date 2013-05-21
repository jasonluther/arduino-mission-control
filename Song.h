#ifndef __SONG_H
#define __SONG_H

#include "Animation.h"
class OutputPin;

class Song : public Animation {
public:
  Song(int num_notes, const int note[], const int duration[]);
  void play(OutputPin *pin, unsigned long time_in_millis);
private:
  int _current_animation_frame;
};

#endif