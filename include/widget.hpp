#ifndef CP_BOII__WIDGET
#define CP_BOII__WIDGET

#pragma once

#include <vector>
#include "../SDL2/include/SDL.h"
#include "renderer.hpp"
// #include "textwidget.hpp"

// class TextWidget;
class Renderer;

class Widget
{
public:
  Widget();

  ~Widget();

  // Getters
  const unsigned int& width() const;
  const unsigned int& height() const;
  const unsigned int& offset_x() const;
  const unsigned int& offset_y() const;
  const unsigned int& padding_x() const;
  const unsigned int& padding_y() const;
  const SDL_Color& foreground_color() const;
  const SDL_Color& background_color() const;

  // Setters
  unsigned int& width();
  unsigned int& height();
  unsigned int& offset_x();
  unsigned int& offset_y();
  unsigned int& padding_x();
  unsigned int& padding_y();
  SDL_Color& foreground_color();
  SDL_Color& background_color();

  // Processors
  void process_event(const SDL_Event& event, bool& event_processed);

  // Children
  // void add_child(const TextWidget& child_widget);

  // Render
  void render(const Renderer& renderer,
              TTF_Font* font,
              unsigned int x,
              unsigned int y) const;

private:
  unsigned int _width;
  unsigned int _height;
  unsigned int _offset_x;
  unsigned int _offset_y;
  unsigned int _padding_x;
  unsigned int _padding_y;

  // std::vector<TextWidget> _children;

  SDL_Color _foreground_color;
  SDL_Color _background_color;
};

#endif