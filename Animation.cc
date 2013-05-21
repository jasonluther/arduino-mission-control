#include "Animation.h"

Animation::Animation(int frames, const int frame[], const int duration[], bool loop) {
  _current_frame = -1;
  _frames = frames;
  _frame = frame;
  _duration = duration;
  _time_to_start_next_frame = 0;
  _loop = loop;
  _iterations = 0;
}

void Animation::animate(unsigned long now) {
  if (_current_frame < 0) {
    _time_to_start_next_frame = now + _duration[0];
    _current_frame = 0;
  }
  if (now >= _time_to_start_next_frame) {
    unsigned long time_left = now - _time_to_start_next_frame;
    while (1) {
      advance_current_frame();
      if (time_left < (unsigned long)_duration[_current_frame]) {
        _time_to_start_next_frame = 
          now + (_duration[_current_frame] - time_left);
        break;
      } else {
        time_left -= _duration[_current_frame];
      }
    }
  }
}

bool Animation::active(void) {
  if (_loop) {
    return true;
  }
  if (_iterations > 0) {
    return false;
  } else {
    return true;
  }
}

void Animation::reset(void) {
  _time_to_start_next_frame = 0;
  _current_frame = -1;
  _iterations = 0;
}

int Animation::get_current_frame(void) {
  return _current_frame;
}

int Animation::get_content(void) {
  if (_current_frame < 0 || !active()) {
    return 0;
  }
  return _frame[_current_frame];
}

int Animation::get_duration(void) {
  if (_current_frame < 0 || !active()) {
    return 0;
  }
  return _duration[_current_frame];
}

int Animation::advance_current_frame(void) {
  if ((_current_frame + 1) < _frames) {
    _current_frame++;
  } else {
    _iterations++;
    _current_frame = 0;
  }
  return _current_frame;
}