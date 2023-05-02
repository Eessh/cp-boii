#include "../include/texture_manager.hpp"
#include <SDL2/SDL_render.h>
#include "../include/font_manager.hpp"
#include "../include/singleton_renderer.hpp"
#include "../log-boii/log_boii.h"

TextureManager* TextureManager::_instance = nullptr;

TextureManager::TextureManager() {}

TextureManager::~TextureManager()
{
  // clearing up textures memory
  for(auto& p : _alphabet_texture_map)
  {
    delete p.second;
  }
}

void TextureManager::create_instance()
{
  if(_instance != nullptr)
  {
    return;
  }
  else
  {
    _instance = new TextureManager();
  }
}

void TextureManager::delete_instance()
{
  delete _instance;
}

TextureManager* TextureManager::get_instance()
{
  return _instance;
}

void TextureManager::load_alphabet_char_textures()
{
  // alphabet ascii ranges: 32 -> 127
  for(unsigned int ascii_code = 32; ascii_code < 128; ascii_code++)
  {
    SDL_Surface* char_surface =
      TTF_RenderGlyph32_Blended(FontManager::get_instance()->get_default_font(),
                                (char)ascii_code,
                                {255, 255, 255, 255});
    if(!char_surface)
    {
      log_error("Error while creating surface for character '%c': %s",
                (char)ascii_code,
                TTF_GetError());
      continue;
      // TODO: handle dis
    }
    DimensionedTexture* alpha_texture = new DimensionedTexture();
    if(!alpha_texture->init(char_surface))
    {
      log_error("Error while creating texture from surface for char '%c': %s",
                (char)ascii_code,
                SDL_GetError());
      SDL_FreeSurface(char_surface);
      delete alpha_texture;
      continue;
      // TODO: handle dis
    }
    SDL_FreeSurface(char_surface);
    _alphabet_texture_map.insert({(char)ascii_code, alpha_texture});
    // SDL_Texture* char_texture = SDL_CreateTextureFromSurface(
    //   SingletonRenderer::get_instance()->renderer(), char_surface);
    // if(!char_texture)
    // {
    //   log_error("Error while creating texture from surface for char '%c': %s",
    //             (char)ascii_code,
    //             SDL_GetError());
    //   SDL_FreeSurface(char_surface);
    //   continue;
    //   // TODO: handle dis
    // }
    // SDL_FreeSurface(char_surface);
    // _alphabet_texture_map.insert({(char)ascii_code, char_texture});
  }
}

SDL_Texture* TextureManager::get_alphabet_char_texture(const char& alphabet)
{
  auto aplhabet_texture_map_iterator = _alphabet_texture_map.find(alphabet);
  if(aplhabet_texture_map_iterator == _alphabet_texture_map.end())
  {
    log_error("Unable to find texture for alphabet: %c, maybe you haven't "
              "loaded alphabets!",
              alphabet);
    return nullptr;
  }
  return (*aplhabet_texture_map_iterator).second->texture();
}

SDL_Texture*
TextureManager::get_colored_alphabet_char_texture(const char& alphabet,
                                                  const SDL_Color& color)
{
  SDL_Surface* char_surface = TTF_RenderGlyph32_Blended(
    FontManager::get_instance()->get_default_font(), alphabet, color);
  if(!char_surface)
  {
    log_error("Error while creating surface for character '%c': %s",
              alphabet,
              TTF_GetError());
    // TODO: handle dis
    return nullptr;
  }
  SDL_Texture* char_texture = SDL_CreateTextureFromSurface(
    SingletonRenderer::get_instance()->renderer(), char_surface);
  SDL_FreeSurface(char_surface);
  return char_texture;
}

SDL_Texture* TextureManager::get_colored_string_texture(const std::string& str,
                                                        const SDL_Color& color)
{
  SDL_Surface* text_surface = TTF_RenderUTF8_Blended(
    FontManager::get_instance()->get_default_font(), str.c_str(), color);
  if(!text_surface)
  {
    log_error("Unable to create colored text surface for text: %s, error: %s",
              str.c_str(),
              TTF_GetError());
    // TODO: handle dis
    return nullptr;
  }
  SDL_Texture* text_texture = SDL_CreateTextureFromSurface(
    SingletonRenderer::get_instance()->renderer(), text_surface);
  if(!text_texture)
  {
    log_error("Unable to create colored text texture from surface for text: "
              "%s, error: %s",
              str.c_str(),
              SDL_GetError());
    SDL_FreeSurface(text_surface);
    // TODO: handle dis
  }
  SDL_FreeSurface(text_surface);
  return text_texture;
}

std::pair<const unsigned int&, const unsigned int&>
TextureManager::get_alphabet_char_texture_dimensions(const char& alphabet)
{
  auto aplhabet_texture_map_iterator = _alphabet_texture_map.find(alphabet);
  if(aplhabet_texture_map_iterator == _alphabet_texture_map.end())
  {
    log_error("Unable to find texture for alphabet: %c, maybe you haven't "
              "loaded alphabets!",
              alphabet);
    return {0, 0};
  }
  return {(*aplhabet_texture_map_iterator).second->width(),
          (*aplhabet_texture_map_iterator).second->height()};
}

// AlphaTexture
DimensionedTexture::DimensionedTexture() : _texture(nullptr) {}

DimensionedTexture::~DimensionedTexture()
{
  SDL_DestroyTexture(_texture);
}

bool DimensionedTexture::init(SDL_Surface* char_surface)
{
  _width = char_surface->w;
  _height = char_surface->h;
  SDL_Texture* char_texture = SDL_CreateTextureFromSurface(
    SingletonRenderer::get_instance()->renderer(), char_surface);
  if(!char_texture)
  {
    log_error("Error while creating texture from surface: %s", SDL_GetError());
    // TODO: handle dis
    return false;
  }
  _texture = char_texture;
  return true;
}

const unsigned int& DimensionedTexture::width() const
{
  return _width;
}

const unsigned int& DimensionedTexture::height() const
{
  return _height;
}

SDL_Texture* DimensionedTexture::texture()
{
  return _texture;
}