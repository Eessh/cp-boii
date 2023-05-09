#include <fstream>
#include <string>
#include <vector>
#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL.h"
#include "../SDL2/include/SDL_syswm.h"
#include "../include/cursor_manager.hpp"
#include "../include/editor_view.hpp"
#include "../include/font_manager.hpp"
#include "../include/singleton_renderer.hpp"
#include "../include/string_widget.hpp"
#include "../include/text_buffers/vector_buffer/vector_buffer.hpp"
#include "../include/texture_manager.hpp"
#include "../include/vertical_view_widget.hpp"
#include "../include/window.hpp"
#include "../log-boii/log_boii.h"

std::vector<std::string>* read_file(const std::string& file_path);

int main(int argc, char** argv)
{
  //  Checking arguments
  if(argc < 2)
  {
    log_fatal("Error: No file is provided as an argument");
    log_info("Usage: cp-boii.exe <file_path>");
    return 1;
  }

  //  Loading file
  std::string file_path(argv[1]);
  std::vector<std::string>* contents = read_file(file_path);
  if(!contents)
  {
    log_fatal("Unable to find file: %s", file_path.c_str());
    return 1;
  }

  //  Initializing SDL
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
  {
    log_fatal("Error while initializing SDL2: %s", SDL_GetError());
    return 1;
  }

  //  Initializing FontManager
  FontManager::create_instance();
  FontManager::get_instance()->initialize();
  FontManager::get_instance()->load_default_font(16);

  //  Initializing CursorManager
  CursorManager::create_instance();
  CursorManager::get_instance()->initialize();

  //  Window config
  WindowConfig config("CP Boii",
                      1080,
                      720,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS |
                        SDL_WINDOW_MOUSE_FOCUS);

  //  Window
  //  setting dark mode for windows
  //  setting window icon
  Window window(config);
#ifdef _WIN64
  window.set_dark_mode();
#elif _WIN32
  window.set_dark_mode();
#endif
  window.set_icon("assets/icons/fire.bmp");

  //  SingleRenderer creation
  SingletonRenderer::create_instance(
    window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE);

  //  Initializing TextureManager
  TextureManager::create_instance();
  //  loading alphabet chars should be done only after initializing SingletonRenderer
  TextureManager::get_instance()->load_alphabet_char_textures();

  //  EditorView widget
  EditorView editor_view_widget(*contents);
  editor_view_widget.set_x(0);
  editor_view_widget.set_y(0);
  editor_view_widget.set_width((int)config.width);
  editor_view_widget.set_height((int)config.height);
  editor_view_widget.set_foreground({211, 198, 170, 255});
  editor_view_widget.set_background({30, 35, 38, 255});
  editor_view_widget.set_active_background({39, 46, 51, 255});
  editor_view_widget.set_line_number_foreground({73, 81, 86, 255});
  editor_view_widget.set_line_number_background({39, 46, 51, 255});
  editor_view_widget.set_line_number_active_foreground({211, 198, 170, 255});
  editor_view_widget.set_line_number_active_background({39, 46, 51, 255});
  editor_view_widget.set_selection_color({128, 128, 128, 128});

  // Freeing memory occupied by file contents
  delete contents;

  bool running = true;
  SDL_Event event;

  while(running)
  {
    if(SDL_WaitEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        running = false;
        break;
      }
      auto _ = editor_view_widget.process_sdl_event(event);
    }

    SingletonRenderer::get_instance()->clear();

    Result<bool, std::string> _ = editor_view_widget.render();
    if(_.error())
    {
      log_fatal("Unable to render editor view widget!");
    }

    SingletonRenderer::get_instance()->present();
  }

  log_info("Cleaning up resources ...");
  CursorManager::get_instance()->delete_instance();
  TextureManager::get_instance()->delete_instance();
  FontManager::get_instance()->delete_instance();
  SingletonRenderer::get_instance()->delete_instance();
  SDL_Quit();

  return 0;
}

std::vector<std::string>* read_file(const std::string& file_path)
{
  std::ifstream file(file_path);
  if(file.is_open())
  {
    auto* contents = new std::vector<std::string>();
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