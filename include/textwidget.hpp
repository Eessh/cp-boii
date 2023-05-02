#ifndef CP_BOII__TEXT_WIDGET
#define CP_BOII__TEXT_WIDGET

#pragma once

#include <string>
#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL.h"
#include "../SDL2_ttf/include/SDL_ttf.h"
#include "renderer.hpp"
#include "texture.hpp"

class Renderer;

class TextWidget
{
public:
  explicit TextWidget(const std::string& text);
  TextWidget(const std::string& text,
             const SDL_Color& foreground_color,
             const SDL_Color& background_color);
  TextWidget(const std::string& text, const Renderer& renderer, TTF_Font* font);
  TextWidget(TextWidget& text_widget);

  // Getters
  [[nodiscard]] const unsigned int& x() const;
  [[nodiscard]] const unsigned int& y() const;
  [[nodiscard]] const unsigned int& width() const;
  [[nodiscard]] const unsigned int& height() const;
  [[nodiscard]] const std::string& text() const;
  [[nodiscard]] const SDL_Color& foreground_color() const;
  [[nodiscard]] const SDL_Color& background_color() const;

  // Setters
  unsigned int& x();
  unsigned int& y();
  unsigned int& width();
  unsigned int& height();
  std::string& text();

  void render(const Renderer& renderer, TTF_Font* font) const;

private:
  unsigned int _x;
  unsigned int _y;
  unsigned int _width;
  unsigned int _height;
  std::string _text;

  SDL_Color _foreground_color;
  SDL_Color _background_color;

  // Texture _texture;
};

#endif