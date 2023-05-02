#include <fstream>
#include <string>
#include <utility>
#include <vector>
#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL.h"
#include "../include/font_manager.hpp"
#include "../include/global_state.hpp"
#include "../include/singleton_renderer.hpp"
#include "../include/string_widget.hpp"
#include "../include/text_buffers/vector_buffer/vector_buffer.hpp"
#include "../include/texture_manager.hpp"
#include "../include/vertical_view_widget.hpp"
#include "../include/window.hpp"
#include "../log-boii/log_boii.h"
#include "SDL_syswm.h"

std::vector<std::string>* read_file(const std::string& file_path);

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    log_fatal("Error: No file is provided as an argument");
    log_info("Usage: cp-boii.exe <file_path>");
    return 1;
  }

  std::string file_path(argv[1]);
  std::vector<std::string>* contents = read_file(file_path);
  if(!contents)
  {
    log_fatal("Unable to find file: %s", file_path.c_str());
    return 1;
  }

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
  {
    log_fatal("Error while initializing SDL2: %s", SDL_GetError());
    return 1;
  }

  FontManager::create_instance();
  FontManager::get_instance()->initialize();
  FontManager::get_instance()->load_default_font(16);

  WindowConfig config("File Content Viewer",
                      1080,
                      720,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS |
                        SDL_WINDOW_MOUSE_FOCUS);

  Window window(config);
  window.set_dark_mode();
  window.set_icon("assets/icons/icon.bmp");

  SingletonRenderer::create_instance(
    window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE);

  TextureManager::create_instance();
  TextureManager::get_instance()->load_alphabet_char_textures();

  VectorBuffer buffer(*contents);

  VerticalViewWidget widget;
  widget.x() = 0;
  widget.y() = 0;
  widget.width() = 1080;
  widget.height() = 720;
  // for(const std::string& line : *contents)
  // {
  //   widget.add_child(new StringWidget(line));
  // }

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
      if(event.type == SDL_KEYDOWN)
      {
        if(event.key.keysym.sym == SDLK_UP)
        {
          buffer.execute_command(Command::MOVE_CURSOR_UP);
        }
        else if(event.key.keysym.sym == SDLK_DOWN)
        {
          buffer.execute_command(Command::MOVE_CURSOR_DOWN);
        }
      }
      widget.process_sdl_event(event);
    }

    // GlobalState::get_instance()->update_time();

    SingletonRenderer::get_instance()->clear();

    widget.remove_all_children();
    std::vector<std::string> text_buffer;
    std::pair<int, int> cursor_coords;
    {
      auto result = buffer.get_buffer();
      if (result.error()) {
        //      TODO: handle dis
        return 1;
      }
      text_buffer = result.take_ok_value();
    }
    {
      auto result = buffer.get_cursor_coords();
      if (result.error()) {
//        TODO: handle dis
        return 1;
      }
      cursor_coords = result.take_ok_value();
    }
    for(int i = 0; i < text_buffer.size(); i++)
    {
      StringWidget* swidget = new StringWidget(text_buffer[i]);
      if(i == cursor_coords.first)
      {
        swidget->foreground_color() = {0, 255, 0, 255};
      }
      widget.add_child(swidget);
    }
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
  return nullptr;
}
