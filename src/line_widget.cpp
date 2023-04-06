#include "../include/line_widget.hpp"

LineWidget::LineWidget(const std::string& text)
: _background_rect_widget(nullptr), _text_widget(nullptr)
{
  _background_rect_widget = new RectangleWidget();
  _text_widget = new TokenizableTextWidget(text);

  this->_height = _text_widget->height();
}

LineWidget::~LineWidget() {
  delete _background_rect_widget;
  delete _text_widget;
}

const std::string& LineWidget::text() const {
  return _text_widget->text();
}

std::string& LineWidget::text() {
  return _text_widget->text();
}

void LineWidget::render() const {
  // setting dimensions
  _background_rect_widget->x() = this->_x;
  _background_rect_widget->y() = this->_y;
  _background_rect_widget->width() = this->width();
  _background_rect_widget->height() = this->height();
  _text_widget->x() = this->_x;
  _text_widget->y() = this->_y;

  // setting colors
  _background_rect_widget->background_color() = this->_background_color;
  _text_widget->foreground_color() = this->_foreground_color;

  _background_rect_widget->render();
  _text_widget->render();
}