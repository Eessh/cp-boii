#ifndef CP_BOII__SINGLETON_RENDERER
#define CP_BOII__SINGLETON_RENDERER

#pragma once

#include "../SDL2/include/SDL.h"
#include "window.hpp"

class Window;

class SingletonRenderer
{
public:
  // deleting copy constructor
  SingletonRenderer(const SingletonRenderer& renderer) = delete;
  // deleting copy operator
  SingletonRenderer operator=(const SingletonRenderer& renderer) = delete;

  // Destructor
  ~SingletonRenderer();

  static void
  create_instance(const Window& window, int driver_index, Uint32 _flags);
  static void delete_instance();

  static SingletonRenderer* get_instance();

  // Media loaders
  void load_default_font();
  void load_font(const std::string& font_file_path);

  // Getters
  [[nodiscard]] const int& driver_index() const;
  [[nodiscard]] const Uint32& flags() const;
  [[nodiscard]] bool has_clip_rect() const;

  // Setters
  int& driver_index();
  Uint32& flags();

  // TODO: need modifications in how these are accessed
  SDL_Renderer* renderer();
  TTF_Font* font();

  // Rendering config setters
  void set_draw_color(const SDL_Color& color) const;
  void set_blend_mode(SDL_BlendMode blend_mode) const;
  void set_target(SDL_Texture* texture) const;
  void set_clip_rect(SDL_Rect clip_rect) const;
  void remove_clip_rect() const;

  // Status check
  [[nodiscard]] bool ok() const;

  // Clear & Present
  void clear() const;
  void present() const;

private:
  bool _ok;
  int _driver_index;

  SDL_Renderer* _renderer;
  TTF_Font* _font;
  Uint32 _flags;

  // Instance pointer
  static SingletonRenderer* _instance;

  // Constructors
  SingletonRenderer();
  SingletonRenderer(const Window& window, int driver_index, Uint32 flags);
};

#endif