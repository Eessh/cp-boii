#ifndef CP_BOII__RENDERER
#define CP_BOII__RENDERER

#pragma once

#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL.h"
#include "base_widget.hpp"
#include "texture.hpp"
#include "texture_manager.hpp"
#include "textwidget.hpp"
#include "widget.hpp"
#include "window.hpp"

class Window;

class Renderer
{
public:
  Renderer(const Window& window, int rendering_driver_index, Uint32 flags);

  ~Renderer();

  // Getters
  [[nodiscard]] int rendering_driver_index() const;
  [[nodiscard]] Uint32 flags() const;

  // Setters
  void set_draw_color(Uint32 r, Uint32 g, Uint32 b, Uint32 a) const;
  void set_blend_mode(SDL_BlendMode blend_mode) const;
  void set_target(SDL_Texture* texture) const;
  void set_clip_rect(SDL_Rect clip_rect) const;
  void remove_clip_rect() const;

  // Clear & Present
  void clear() const;
  void present() const;

  // Status check
  [[nodiscard]] bool ok() const;

private:
  int _rendering_driver_index;
  Uint32 _flags;

  SDL_Renderer* _renderer;
  bool _ok;

  friend class BaseWidget;
  friend class Texture;
  friend class TextWidget;
  friend class Widget;
  friend class TextureManager;
};

#endif