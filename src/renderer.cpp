#include "../include/renderer.hpp"
#include "../log-boii/log_boii.h"
#include "SDL_render.h"

Renderer::Renderer(const Window& window,
                   int rendering_driver_index,
                   Uint32 flags)
  : _rendering_driver_index(rendering_driver_index), _flags(flags)
{
  _renderer =
    SDL_CreateRenderer(window._window, _rendering_driver_index, _flags);
  if(!_renderer)
  {
    log_fatal("Error while creating renderer: %s", SDL_GetError());
    _ok = false;
  }
}

Renderer::~Renderer()
{
  log_info("Freeing up resources used by renderer...");
  SDL_DestroyRenderer(_renderer);
}

int Renderer::rendering_driver_index() const
{
  return _rendering_driver_index;
}

void Renderer::set_draw_color(Uint32 r, Uint32 g, Uint32 b, Uint32 a) const
{
  SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void Renderer::set_blend_mode(SDL_BlendMode blend_mode) const
{
  SDL_SetRenderDrawBlendMode(_renderer, blend_mode);
}

void Renderer::set_target(SDL_Texture* texture) const
{
  SDL_SetRenderTarget(_renderer, texture);
}

void Renderer::set_clip_rect(SDL_Rect clip_rect) const
{
  SDL_RenderSetClipRect(_renderer, &clip_rect);
}

void Renderer::remove_clip_rect() const
{
  SDL_RenderSetClipRect(_renderer, nullptr);
}

void Renderer::clear() const
{
  SDL_RenderClear(_renderer);
}

void Renderer::present() const
{
  SDL_RenderPresent(_renderer);
}

Uint32 Renderer::flags() const
{
  return _flags;
}

bool Renderer::ok() const
{
  return _ok;
}