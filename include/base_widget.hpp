#ifndef CP_BOII__BASE_WIDGET
#define CP_BOII__BASE_WIDGET

#include <algorithm>
#include <vector>
// #include "renderer.hpp"
#include "../SDL2/include/SDL.h"

// class Renderer;

class BaseWidget
{
public:
  BaseWidget();

  ~BaseWidget();

  // Getters
  const unsigned int& x() const;
  const unsigned int& y() const;
  const unsigned int& width() const;
  const unsigned int& height() const;
  const SDL_Color& foreground_color() const;
  const SDL_Color& background_color() const;

  // Setters
  unsigned int& x();
  unsigned int& y();
  unsigned int& width();
  unsigned int& height();
  SDL_Color& foreground_color();
  SDL_Color& background_color();

  // Children methods
  void add_child(BaseWidget* child);
  void remove_child(BaseWidget* child);

  // Processors
  virtual void process_event(const SDL_Event& event) = 0;

  // Render
  virtual void render() const = 0;

protected:
  unsigned int _x;
  unsigned int _y;
  unsigned int _width;
  unsigned int _height;

  SDL_Color _foreground_color;
  SDL_Color _background_color;

  std::vector<BaseWidget*> _children;
};

#endif