#include "../include/singleton_renderer.hpp"
#include "../log-boii/log_boii.h"

SingletonRenderer* SingletonRenderer::_instance = nullptr;

SingletonRenderer::SingletonRenderer(const Window& window,
                                     int driver_index,
                                     Uint32 flags)
  : _driver_index(driver_index), _flags(flags)
{
  log_info("Creating SingletonRenderer...");
  _renderer = SDL_CreateRenderer(window._window, _driver_index, _flags);
  if(!_renderer)
  {
    _ok = false;
    // TODO: handle dis
  }
}

SingletonRenderer::~SingletonRenderer()
{
  log_info("Freeing up resources used by SingletonRenderer...");
  SDL_DestroyRenderer(this->_renderer);
}

void SingletonRenderer::create_instance(const Window& window,
                                        int driver_index,
                                        Uint32 flags)
{
  if(_instance != nullptr)
  {
    log_trace("SingletonRenderer already exists, use "
              "SingletonRenderer::get_instance()");
    return;
  }
  else
  {
    log_info("Creating SingletonRenderer instance...");
    _instance = new SingletonRenderer(window, driver_index, flags);
  }
}

void SingletonRenderer::delete_instance()
{
  log_info("Deleting SingletonRenderer instance");
  delete _instance;
}

SingletonRenderer* SingletonRenderer::get_instance()
{
  return _instance;
}

void SingletonRenderer::load_default_font()
{
  this->_font = TTF_OpenFont("C:/Windows/Fonts/consola.ttf", 18);
  if(!this->_font)
  {
    _ok = false;
    log_fatal("Error while loading default font: %s", TTF_GetError());
  }
}

void SingletonRenderer::load_font(const std::string& font_file_path)
{
  this->_font = TTF_OpenFont(font_file_path.c_str(), 18);
  if(!this->_font)
  {
    _ok = false;
    log_fatal("Unable to load font: %s, error occurred: %s",
              font_file_path.c_str(),
              TTF_GetError());
    // TODO: handle dis
  }
}

const int& SingletonRenderer::driver_index() const
{
  return _driver_index;
}

const Uint32& SingletonRenderer::flags() const
{
  return _flags;
}

int& SingletonRenderer::driver_index()
{
  return _driver_index;
}

Uint32& SingletonRenderer::flags()
{
  return _flags;
}

SDL_Renderer* SingletonRenderer::renderer()
{
  return _renderer;
}

TTF_Font* SingletonRenderer::font()
{
  return _font;
}

void SingletonRenderer::set_draw_color(const SDL_Color& color) const
{
  SDL_SetRenderDrawColor(this->_renderer, color.r, color.g, color.b, color.a);
}

void SingletonRenderer::set_blend_mode(SDL_BlendMode blend_mode) const
{
  SDL_SetRenderDrawBlendMode(this->_renderer, blend_mode);
}

void SingletonRenderer::set_target(SDL_Texture* texture) const
{
  SDL_SetRenderTarget(this->_renderer, texture);
}

void SingletonRenderer::set_clip_rect(SDL_Rect clip_rect) const
{
  SDL_RenderSetClipRect(this->_renderer, &clip_rect);
}

void SingletonRenderer::remove_clip_rect() const
{
  SDL_RenderSetClipRect(this->_renderer, nullptr);
}

bool SingletonRenderer::ok() const
{
  return _ok;
}

void SingletonRenderer::clear() const
{
  SDL_RenderClear(this->_renderer);
}

void SingletonRenderer::present() const
{
  SDL_RenderPresent(this->_renderer);
}