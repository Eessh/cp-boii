#ifndef CP_BOII__LINE_WIDGET
#define CP_BOII__LINE_WIDGET

#pragma once

#include "rectangle_widget.hpp"
#include "tokenizable_text_widget.hpp"

class LineWidget: public BaseWidget {
public:
  LineWidget(const std::string& text);
  ~LineWidget();

  // Getters
  const std::string& text() const;

  // Setters
  std::string& text();

  void render() const;

private:
  RectangleWidget* _background_rect_widget;
  TokenizableTextWidget* _text_widget;
};

#endif