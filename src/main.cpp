#include <iostream>
#include <string>
#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL.h"
#include "../SDL2_ttf/include/SDL_ttf.h"
#include "../include/font_manager.hpp"
#include "../include/renderer.hpp"
#include "../include/singleton_renderer.hpp"
#include "../include/string_widget.hpp"
#include "../include/vertical_view_widget.hpp"
#include "../include/window.hpp"
#include "../log-boii/log_boii.h"

int main(int argc, char** argv)
{

  log_trace("Initializing video & timer subsystems...");
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
  {
    log_fatal("Error while initializing video & timer subsystems: %s",
              SDL_GetError());
    return 1;
  }

  // log_trace("Initializing TTF extension...");
  // if(TTF_Init() != 0)
  // {
  //   log_fatal("Error while initializing TTF extension: %s", TTF_GetError());
  //   SDL_Quit();
  //   return 1;
  // }
  FontManager::create_instance();
  FontManager::get_instance()->initialize();
  FontManager::get_instance()->load_default_font(18);

  // log_trace("Loading system font...");
  // TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/consola.ttf", 16);
  // if(!font)
  // {
  //   log_fatal("Error while loading font: %s", TTF_GetError());
  //   TTF_Quit();
  //   SDL_Quit();
  //   return 1;
  // }

  WindowConfig window_config = WindowConfig(
    "CP Boii",
    1080,
    720,
    SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE |
      SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);

  Window window(window_config);

  SingletonRenderer::create_instance(
    window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  SingletonRenderer::get_instance()->load_default_font();

  TextureManager::create_instance();
  TextureManager::get_instance()->load_alphabet_char_textures();

  StringWidget swidget("Madda Gudu");

  VerticalViewWidget vwidget;
  std::string s = "";
  for(unsigned int i = 0; i < 40; i++)
  {
    s.push_back('a');
  }
  s.push_back(' ');
  for(unsigned int i = 0; i < 40; i++)
  {
    s.push_back('a');
  }
  vwidget.add_child(new StringWidget(
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
  for(unsigned int i = 0; i < 2000; i++)
  {
    vwidget.add_child(new StringWidget(s));
  }
  vwidget.add_child(new StringWidget("Hola"));
  vwidget.add_child(new StringWidget("Cola"));

  // Renderer renderer(
  //   window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE);
  // Widget widget;
  // TextWidget text_widget("Madda Gudu");
  // widget.add_child(text_widget);

  bool running = true;
  SDL_Event event;
  bool event_processed = false;

  while(running)
  {
    if(SDL_WaitEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        log_info("Got EXIT signal.");
        running = false;
        continue;
      }
      if(event.type == SDL_MOUSEMOTION)
      {
        event_processed = false;
      }
      if(event.type == SDL_MOUSEBUTTONUP)
      {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
          log_info("Left click at: (%d, %d)", event.button.x, event.button.y);
        }
        else if(event.button.button == SDL_BUTTON_RIGHT)
        {
          log_info("Right click at: (%d, %d)", event.button.x, event.button.y);
        }
        event_processed = true;
      }
      // widget.process_event(event, event_processed);
      swidget.process_event(event);
      vwidget.process_event(event);
    }

    // if(!event_processed)
    //   continue;

    // renderer.set_draw_color(128, 128, 128, 255);
    // renderer.clear();
    SingletonRenderer::get_instance()->clear();

    // widget.width() = 100;
    // widget.height() = 100;
    // widget.render(renderer, font, 20, 20);

    // text_widget.render(renderer, font);

    swidget.x() = 20;
    swidget.y() = 20;
    // swidget.render();

    vwidget.x() = 0;
    vwidget.y() = 0;
    vwidget.width() = 1080;
    vwidget.height() = 720;
    // vwidget.background_color() = {128, 128, 128, 255};
    vwidget.render();

    // renderer.present();
    SingletonRenderer::get_instance()->present();
  }

  log_info("Cleaning up resources ...");
  FontManager::get_instance()->delete_instance();
  TextureManager::get_instance()->delete_instance();
  SingletonRenderer::get_instance()->delete_instance();
  TTF_Quit();
  SDL_Quit();

  return 0;
}