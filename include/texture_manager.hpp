#ifndef CP_BOII__TEXTURE_MANAGER
#define CP_BOII__TEXTURE_MANAGER

#include <string>
#include <unordered_map>
#include "../SDL2/include/SDL.h"
#include "../SDL2_ttf/include/SDL_ttf.h"

class AlphaTexture
{
public:
  AlphaTexture();
  ~AlphaTexture();

  bool init(SDL_Surface* char_surface);

  const unsigned int& width() const;
  const unsigned int& height() const;
  SDL_Texture* texture();

private:
  unsigned int _width;
  unsigned int _height;

  SDL_Texture* _texture;
};

class TextureManager
{
public:
  // Deleting copy constructor
  TextureManager(const TextureManager& texture_manager) = delete;
  // Deteting copy operator
  TextureManager operator=(const TextureManager& texture_manager) = delete;

  ~TextureManager();

  static void create_instance();
  static TextureManager* get_instance();
  static void delete_instance();

  void load_alphabet_char_textures();
  SDL_Texture* get_alphabet_char_texture(const char& alphabet);
  std::pair<const unsigned int&, const unsigned int&>
  get_alphabet_char_texture_dimensions(const char& alphabet);

  // TODO: Media texture loaders

private:
  std::unordered_map<char, AlphaTexture*> _alphabet_texture_map;

  // Constructors
  TextureManager();

  static TextureManager* _instance;
};

#endif