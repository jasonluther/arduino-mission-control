#ifndef __ANIMATION_H
#define __ANIMATION_H

class Animation {
private:
  int _current_frame;
  int _frames;
  const int *_frame;
  const int *_duration;
  unsigned long _time_to_start_next_frame;
  bool _loop;
  int _iterations;

public:
  Animation(int frames, const int frame[], const int duration[], bool loop = true);
  void animate(unsigned long time_in_millis);
  int get_content(void);
  int get_current_frame(void);
  int get_duration(void);
  bool active(void);
  void reset();
private:
  int advance_current_frame(void);
};

#endif