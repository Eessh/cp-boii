#ifndef CP_BOII__FONT_MANAGER
#define CP_BOII__FONT_MANAGER

#pragma once

#include <string>
#include <unordered_map>
#include "../SDL2_ttf/include/SDL_ttf.h"

class FontManager
{
public:
  // Deleting copy constructor
  FontManager(const FontManager& font_manager) = delete;
  // Deleting copy operator
  FontManager operator=(const FontManager& font_manager) = delete;

  // Destructor
  ~FontManager();

  static void create_instance();
  static FontManager* get_instance();
  static void delete_instance();

  void initialize();

  // Loaders
  void load_default_font(unsigned int font_size);
  void load_font(const std::string& font_file_path,
                 unsigned int font_size,
                 const std::string& font_name_to_assign);

  // Getters
  TTF_Font* get_default_font();
  TTF_Font* get_font(const std::string& font_name_assigned);
  std::pair<unsigned int, unsigned int>
  get_char_dimensions(const char& character);
  std::pair<unsigned int, unsigned int>
  get_text_dimensions(const std::string& text);

  bool ok() const;

private:
  std::unordered_map<std::string, TTF_Font*> _font_map;
  bool _ok;

  // constructors
  FontManager();

  static FontManager* _instance;
};

#endif