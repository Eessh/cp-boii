#include "../include/animation_event.hpp"

AnimationEvent::AnimationEvent(BaseWidget* widget)
  : _widget(widget), _pixels_per_frame(0), _current_frame(0)
{}

AnimationEvent::~AnimationEvent() {}