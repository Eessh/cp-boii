#include "../include/window.hpp"
#include "../log-boii/log_boii.h"

Window::Window(const std::string& title,
               unsigned int width,
               unsigned int height,
               Uint32 flags)
  : _title(title)
  , _x(SDL_WINDOWPOS_CENTERED)
  , _y(SDL_WINDOWPOS_CENTERED)
  , _width(width)
  , _height(height)
  , _flags(flags)
{
  _window = SDL_CreateWindow(_title.c_str(), _x, _y, _width, _height, _flags);
  if(!_window)
  {
    log_fatal("Error while creating window: %s", SDL_GetError());
    _ok = false;
    _window = NULL;
  }
}

Window::Window(const std::string& title,
               unsigned int x,
               unsigned int y,
               unsigned int width,
               unsigned int height,
               Uint32 flags)
  : _title(title), _x(x), _y(y), _width(width), _height(height), _flags(flags)
{
  _window = SDL_CreateWindow(_title.c_str(), _x, _y, _width, _height, _flags);
  if(!_window)
  {
    log_fatal("Error while creating window: %s", SDL_GetError());
    _ok = false;
    _window = NULL;
  }
}

Window::Window(const WindowConfig& config)
  : _title(config.title)
  , _x(config.x)
  , _y(config.y)
  , _width(config.width)
  , _height(config.height)
  , _flags(config.flags)
{
  _window = SDL_CreateWindow(_title.c_str(), _x, _y, _width, _height, _flags);
  if(!_window)
  {
    log_fatal("Error while creating window: %s", SDL_GetError());
    _ok = false;
    _window = NULL;
  }
}

Window::~Window()
{
  log_info("Freeing up resources used by window...");
  SDL_DestroyWindow(_window);
}

unsigned int Window::x() const
{
  return _x;
}

unsigned int Window::y() const
{
  return _y;
}

unsigned int Window::width() const
{
  return _width;
}

unsigned int Window::height() const
{
  return _height;
}

const std::string& Window::title() const
{
  return _title;
}

unsigned int& Window::x()
{
  return _x;
}

unsigned int& Window::y()
{
  return _y;
}

unsigned int& Window::width()
{
  return _width;
}

unsigned int& Window::height()
{
  return _height;
}

std::string& Window::title()
{
  return _title;
}

bool Window::ok() const
{
  return _ok;
}