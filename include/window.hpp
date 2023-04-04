#ifndef CP_BOII__WINDOW
#define CP_BOII__WINDOW

#pragma once

#include <string>
#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL.h"
#include "renderer.hpp"
#include "singleton_renderer.hpp"

class WindowConfig
{
public:
  std::string title;
  unsigned int x;
  unsigned int y;
  unsigned int width;
  unsigned int height;
  Uint32 flags;

  WindowConfig(const std::string& title,
               unsigned int width,
               unsigned int height,
               Uint32 flags)
    : title(title)
    , x(SDL_WINDOWPOS_CENTERED)
    , y(SDL_WINDOWPOS_CENTERED)
    , width(width)
    , height(height)
    , flags(flags)
  {}

  WindowConfig(const std::string& title,
               unsigned int x,
               unsigned int y,
               unsigned int width,
               unsigned int height,
               Uint32 flags)
    : title(title), x(x), y(y), width(width), height(height), flags(flags)
  {}
};

class Window
{
public:
  Window(const std::string& title,
         unsigned int width,
         unsigned int height,
         Uint32 flags);

  Window(const std::string& title,
         unsigned int x,
         unsigned int y,
         unsigned int width,
         unsigned int height,
         Uint32 flags);

  Window(const WindowConfig& config);

  ~Window();

  // Getters
  unsigned int x() const;
  unsigned int y() const;
  unsigned int width() const;
  unsigned int height() const;
  const std::string& title() const;

  // Setters
  unsigned int& x();
  unsigned int& y();
  unsigned int& width();
  unsigned int& height();
  std::string& title();

  // Status check
  bool ok() const;

private:
  unsigned int _x;
  unsigned int _y;
  unsigned int _width;
  unsigned int _height;
  Uint32 _flags;
  std::string _title;

  SDL_Window* _window;
  bool _ok;

  friend class Renderer;
  friend class SingletonRenderer;
};

#endif