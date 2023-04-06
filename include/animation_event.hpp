#ifndef CP_BOII__ANIMATION_EVENT
#define CP_BOII__ANIMATION_EVENT

#pragma once

#include "base_widget.hpp"

class AnimationEvent
{
public:
  AnimationEvent(BaseWidget* widget);
  ~AnimationEvent();

private:
  BaseWidget* _widget;
  unsigned int _pixels_per_frame;
  unsigned int _current_frame;
};

#endif