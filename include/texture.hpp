#ifndef CP_BOII__TEXTURE
#define CP_BOII__TEXTURE

#include <string>
#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL.h"
#include "renderer.hpp"

class Renderer;

class Texture
{
public:
  Texture();
  Texture(const Renderer& renderer, SDL_Surface* surface);
  Texture(Texture& texture);

  ~Texture();

  // Media Loaders
  bool load(const std::string& filepath);

  // Getters
  unsigned int width() const;
  unsigned int height() const;

  // Status check
  bool ok() const;

  // Renders
  void render(const Renderer& renderer, unsigned int x, unsigned int y) const;

private:
  unsigned int _width;
  unsigned int _height;
  bool _ok;

  SDL_Texture* _texture;
};

#endif