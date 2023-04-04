#include "../include/widget.hpp"
#include "SDL_events.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "textwidget.hpp"

Widget::Widget()
  : _width(0)
  , _height(0)
  , _padding_x(0)
  , _padding_y(0)
  , _foreground_color({255, 255, 255, 255})
  , _background_color({0, 0, 0, 0})
// , _children({})
{}

Widget::~Widget() {}

const unsigned int& Widget::width() const
{
  return _width;
}

const unsigned int& Widget::height() const
{
  return _height;
}

const unsigned int& Widget::offset_x() const
{
  return _offset_x;
}

const unsigned int& Widget::offset_y() const
{
  return _offset_y;
}

const unsigned int& Widget::padding_x() const
{
  return _padding_x;
}

const unsigned int& Widget::padding_y() const
{
  return _padding_y;
}

const SDL_Color& Widget::foreground_color() const
{
  return _foreground_color;
}

const SDL_Color& Widget::background_color() const
{
  return _background_color;
}

unsigned int& Widget::width()
{
  return _width;
}

unsigned int& Widget::height()
{
  return _height;
}

unsigned int& Widget::offset_x()
{
  return _offset_x;
}

unsigned int& Widget::offset_y()
{
  return _offset_y;
}

unsigned int& Widget::padding_x()
{
  return _padding_x;
}

unsigned int& Widget::padding_y()
{
  return _padding_y;
}

SDL_Color& Widget::foreground_color()
{
  return _foreground_color;
}

SDL_Color& Widget::background_color()
{
  return _background_color;
}

void Widget::process_event(const SDL_Event& event, bool& event_processed)
{
  switch(event.type)
  {
  case SDL_MOUSEBUTTONUP: {
    event_processed = false;
    break;
  }
  case SDL_MOUSEWHEEL: {
    if(event.wheel.y > 0)
    {
      // scroll up
      _padding_y += 4 * event.wheel.y;
    }
    if(event.wheel.y < 0)
    {
      // scroll down
      _padding_y += 4 * event.wheel.y;
    }
    if(event.wheel.x > 0)
    {
      // scroll right
      _padding_x -= 4 * event.wheel.x;
    }
    if(event.wheel.x < 0)
    {
      // scroll left
      _padding_x -= 4 * event.wheel.x;
    }
    event_processed = true;
    break;
  }
  case SDL_MULTIGESTURE: {
    break;
  }
  default: {
    event_processed = false;
    break;
  }
  }
}

// void Widget::add_child(const TextWidget& child_widget)
// {
//   _children.push_back(child_widget);
// }

void Widget::render(const Renderer& renderer,
                    TTF_Font* font,
                    unsigned int x,
                    unsigned int y) const
{
  SDL_Rect background_rect{static_cast<int>(x),
                           static_cast<int>(y),
                           static_cast<int>(_width),
                           static_cast<int>(_height)};
  renderer.set_clip_rect(background_rect);
  renderer.set_draw_color(_background_color.r,
                          _background_color.g,
                          _background_color.b,
                          _background_color.a);
  SDL_RenderFillRect(renderer._renderer, &background_rect);
  // for(TextWidget& child : _children)
  // {
  //   child.x() = x+_padding_x;
  //   child.y() = y+_padding_y;
  //   child.render(renderer, font);
  // }
  // for (unsigned int i=0; i<_children.size(); i++) {
  //   _children[i].x() = x+_padding_x;
  //   _children[i].y() = y+_padding_y;
  //   _children[i].render(renderer, font);
  // }
  renderer.remove_clip_rect();
}