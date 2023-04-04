#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL.h"
#include "../include/font_manager.hpp"
#include "../include/global_state.hpp"
#include "../include/singleton_renderer.hpp"
#include "../include/string_widget.hpp"
#include "../include/texture_manager.hpp"
#include "../include/vertical_view_widget.hpp"
#include "../include/window.hpp"
#include "../log-boii/log_boii.h"

std::vector<std::string>* read_file(const std::string& file_path);

int main(int argc, char** argv)
{

  if(argc < 2)
  {
    log_fatal("Error: No file is provided as an argument");
    log_info("Usage: cp-boii.exe <file_path>");
    return 1;
  }

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
  {
    log_fatal("Error while initializing SDL2: %s", SDL_GetError());
    return 1;
  }

  FontManager::create_instance();
  FontManager::get_instance()->initialize();
  FontManager::get_instance()->load_default_font(18);

  WindowConfig config("File Content Viewer",
                      1080,
                      720,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS |
                        SDL_WINDOW_MOUSE_FOCUS);

  Window window(config);

  SingletonRenderer::create_instance(
    window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE);

  TextureManager::create_instance();
  TextureManager::get_instance()->load_alphabet_char_textures();

  std::string file_path(argv[1]);
  std::vector<std::string>* contents = read_file(file_path);

  VerticalViewWidget widget;
  widget.x() = 0;
  widget.y() = 0;
  widget.width() = 1080;
  widget.height() = 720;
  for(const std::string& line : *contents)
  {
    widget.add_child(new StringWidget(line));
  }

  // Freeing memory occupied by file contents
  delete contents;

  bool running = true;
  SDL_Event event;

  // GlobalState::create_instance();

  while(running)
  {
    if(SDL_WaitEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        running = false;
        continue;
      }
      widget.process_event(event);
    }

    // GlobalState::get_instance()->update_time();

    SingletonRenderer::get_instance()->clear();
    widget.render();
    SingletonRenderer::get_instance()->present();
  }

  log_info("Cleaning up resources ...");
  GlobalState::get_instance()->delete_instance();
  FontManager::get_instance()->delete_instance();
  TextureManager::get_instance()->delete_instance();
  SingletonRenderer::get_instance()->delete_instance();
  SDL_Quit();

  return 0;
}

std::vector<std::string>* read_file(const std::string& file_path)
{
  std::ifstream file(file_path);
  if(file.is_open())
  {
    std::vector<std::string>* contents = new std::vector<std::string>();
    while(file.good())
    {
      contents->push_back("");
      std::getline(file, contents->back());
    }
    return contents;
  }
  log_error("Unable to open file: %s", file_path.c_str());
  return {};
}
