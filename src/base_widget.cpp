#include "../include/base_widget.hpp"

BaseWidget::BaseWidget()
  : _x(0)
  , _y(0)
  , _width(0)
  , _height(0)
  , _foreground_color({255, 255, 255, 255})
  , _background_color({0, 0, 0, 255})
  , _children({})
{}

BaseWidget::~BaseWidget()
{
  while(!_children.empty())
  {
    BaseWidget* child = _children.back();
    _children.pop_back();
    delete child;
  }
}

const unsigned int& BaseWidget::x() const
{
  return _x;
}

const unsigned int& BaseWidget::y() const
{
  return _y;
}

const unsigned int& BaseWidget::width() const
{
  return _width;
}

const unsigned int& BaseWidget::height() const
{
  return _height;
}

const SDL_Color& BaseWidget::foreground_color() const
{
  return _foreground_color;
}

const SDL_Color& BaseWidget::background_color() const
{
  return _background_color;
}

unsigned int& BaseWidget::x()
{
  return _x;
}

unsigned int& BaseWidget::y()
{
  return _y;
}

unsigned int& BaseWidget::width()
{
  return _width;
}

unsigned int& BaseWidget::height()
{
  return _height;
}

SDL_Color& BaseWidget::foreground_color()
{
  return _foreground_color;
}

SDL_Color& BaseWidget::background_color()
{
  return _background_color;
}

void BaseWidget::add_child(BaseWidget* child)
{
  _children.push_back(child);
}

void BaseWidget::remove_child(BaseWidget* child)
{
  std::remove(_children.begin(), _children.end(), child);
}