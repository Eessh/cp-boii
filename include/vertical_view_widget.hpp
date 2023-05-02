#ifndef CP_BOII__VERTICAL_VIEW_WIDGET
#define CP_BOII__VERTICAL_VIEW_WIDGET

#pragma once

#include "base_widget.hpp"

class VerticalViewWidget : public BaseWidget
{
public:
  VerticalViewWidget();

  ~VerticalViewWidget() = default;

  // Getters
  [[nodiscard]] const unsigned int& padding_x() const;
  [[nodiscard]] const unsigned int& padding_y() const;
  [[nodiscard]] const int& scroll_offset_x() const;
  [[nodiscard]] const int& scroll_offset_y() const;

  // Setters
  unsigned int& padding_x();
  unsigned int& padding_y();
  int& scroll_offset_x();
  int& scroll_offset_y();

  // void add_child(BaseWidget* child);
  // void remove_child(BaseWidget* child);

  // Processors
  void process_sdl_event(const SDL_Event& event);

  // Render
  void render() const;

private:
  unsigned int _padding_x;
  unsigned int _padding_y;
  unsigned int _children_width;
  unsigned int _children_height;

  // Scrolling shit
  bool _is_scrolling;
  unsigned int _scroll_sensitivity;
  int _scroll_acceleration;
  double _scroll_friction;
  int _scroll_offset_x;
  int _scroll_offset_y;
  int _scroll_offset_x_prev;
  int _scroll_offset_y_prev;

  // Utility functions
  bool point_lies_inside(Sint32 x, Sint32 y) const;
};

#endif