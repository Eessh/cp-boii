#include "../include/font_manager.hpp"
#include "../log-boii/log_boii.h"

FontManager* FontManager::_instance = nullptr;

FontManager::FontManager() {}

FontManager::~FontManager()
{
  // clearing up fonts memory
  log_trace("Clearing up fonts memory...");
  for(auto& p : _font_map)
  {
    TTF_CloseFont(p.second);
  }
  log_info("Quitting SDL_TTF extension...");
  TTF_Quit();
}

void FontManager::create_instance()
{
  if(_instance != nullptr)
  {
    log_warn(
      "Font Manager instance already exists, use FontManager::get_instance()");
    return;
  }
  log_info("Creating Font Manager...");
  _instance = new FontManager();
}

void FontManager::delete_instance()
{
  log_info("Deleting Font Manager instance...");
  delete _instance;
}

FontManager* FontManager::get_instance()
{
  return _instance;
}

void FontManager::initialize()
{
  log_trace("Initializing SDL_TTF extension...");
  if(TTF_Init() != 0)
  {
    log_fatal("Error while initializing TTF extension: %s", TTF_GetError());
    _ok = false;
    // TODO: handle dis
  }
}

void FontManager::load_default_font(unsigned int font_size)
{
  log_info("Loading default font: "
           "../../assets/fonts/JetBrainsMono-2.304/fonts/ttf/"
           "JetBrainsMonoNL-Regular.ttf...");
  TTF_Font* default_font =
    //     TTF_OpenFont("C:/Windows/Fonts/consola.ttf", font_size);
    //    TTF_OpenFont("assets/fonts/NotoSansMono/NotoSansMono-Regular.ttf",
    //                 font_size);
    TTF_OpenFont(
      "assets/fonts/JetBrainsMono-2.304/fonts/ttf/JetBrainsMonoNL-Regular.ttf",
      static_cast<int>(font_size));
  if(!default_font)
  {
    log_fatal("Error while loading default font: %s", TTF_GetError());
    _ok = false;
    // TODO: handle dis
  }
  _font_map.insert({"default", default_font});
}

TTF_Font* FontManager::get_default_font()
{
  auto font_map_iterator = _font_map.find("default");
  if(font_map_iterator == _font_map.end())
  {
    log_error("Unable to find default font, maybe you haven't loaded it!");
    return nullptr;
  }
  return (*font_map_iterator).second;
}

void FontManager::load_font(const std::string& font_file_path,
                            unsigned int font_size,
                            const std::string& font_name_to_assign)
{
  log_info("Loading font: %s", font_file_path.c_str());
  TTF_Font* font = TTF_OpenFont(font_file_path.c_str(), font_size);
  if(!font)
  {
    log_fatal("Unable to load font: %s, error: %s",
              font_file_path.c_str(),
              TTF_GetError());
    _ok = false;
    // TODO: handle dis
  }
  _font_map.insert({font_name_to_assign, font});
}

TTF_Font* FontManager::get_font(const std::string& font_name_assigned)
{
  auto font_map_iterator = _font_map.find(font_name_assigned);
  if(font_map_iterator == _font_map.end())
  {
    log_error("Unable to find font: %s, maybe you haven't loaded it!",
              font_name_assigned.c_str());
    return nullptr;
  }
  return (*font_map_iterator).second;
}

std::pair<unsigned int, unsigned int>
FontManager::get_char_dimensions(const char& character)
{
  int char_width, char_height;
  std::string s;
  s.push_back(character);
  TTF_SizeText(get_default_font(), s.c_str(), &char_width, &char_height);
  return {char_width, char_height};
}

std::pair<unsigned int, unsigned int>
FontManager::get_text_dimensions(const std::string& text)
{
  int text_width, text_height;
  TTF_SizeText(get_default_font(), text.c_str(), &text_width, &text_height);
  return {text_width, text_height};
}

bool FontManager::ok() const
{
  return _ok;
}