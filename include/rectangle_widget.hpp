#ifndef CP_BOII__RECTANGLE_WIDGET
#define CP_BOII__RECTANGLE_WIDGET

#pragma once

#include "base_widget.hpp"

typedef enum class RectangleStyle
{
  FILLED,
  OUTLINED
} RectangleStyle;

class RectangleWidget : public BaseWidget
{
public:
  RectangleWidget();
  ~RectangleWidget();

  // Getters
  [[nodiscard]] const RectangleStyle& style() const;

  // Setters
  RectangleStyle& style();

  // Processors
  void process_sdl_event(const SDL_Event& event);

  void render() const;

private:
  RectangleStyle _style;
};

#endif