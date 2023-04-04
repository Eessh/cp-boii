#include "../include/texture.hpp"
#include "log_boii.h"

Texture::Texture() : _width(0), _height(0), _texture(nullptr) {}

Texture::Texture(const Renderer& renderer, SDL_Surface* surface)
  : _width(0), _height(0), _texture(nullptr)
{
  // log_trace("Creating texture from surface ...");
  _texture = SDL_CreateTextureFromSurface(renderer._renderer, surface);
  _width = surface->w;
  _height = surface->h;
  if(!_texture)
  {
    // log_error("Unable to create texture from surface: %s", SDL_GetError());
    _ok = false;
    _texture = nullptr;
  }
  // log_trace("Freeing surface...");
  SDL_FreeSurface(surface);
}

Texture::Texture(Texture& texture)
  : _width(texture.width()), _height(texture.height()), _texture(nullptr)
{
  _texture = texture._texture;
}

Texture::~Texture()
{
  // log_info("Destroying texture...");
  SDL_DestroyTexture(_texture);
}

bool Texture::load(const std::string& filepath)
{
  return false;
}

unsigned int Texture::width() const
{
  return _width;
}

unsigned int Texture::height() const
{
  return _height;
}

bool Texture::ok() const
{
  return _ok;
}

void Texture::render(const Renderer& renderer,
                     unsigned int x,
                     unsigned int y) const
{
  SDL_Rect destination_rect{static_cast<int>(x),
                            static_cast<int>(y),
                            static_cast<int>(_width),
                            static_cast<int>(_height)};
  SDL_RenderCopy(renderer._renderer, _texture, nullptr, &destination_rect);
}