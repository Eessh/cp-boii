#include "../include/textwidget.hpp"
#include "SDL_ttf.h"
#include "texture.hpp"

TextWidget::TextWidget(const std::string& text)
  : _x(0)
  , _y(0)
  , _width(0)
  , _height(0)
  , _text(text)
  , _foreground_color({255, 255, 255, 255})
  , _background_color({0, 0, 0, 0})
{}

TextWidget::TextWidget(const std::string& text,
                       const SDL_Color& foreground_color,
                       const SDL_Color& background_color)
  : _x(0)
  , _y(0)
  , _width(0)
  , _height(0)
  , _text(text)
  , _foreground_color(foreground_color)
  , _background_color(background_color)
{}

TextWidget::TextWidget(const std::string& text,
                       const Renderer& renderer,
                       TTF_Font* font)
  : _x(0)
  , _y(0)
  , _text(text)
  , _foreground_color({255, 255, 255, 255})
  , _background_color({0, 0, 0, 0})
{
  SDL_Surface* surface = TTF_RenderText_Shaded(
    font, _text.c_str(), _foreground_color, _background_color);
  if(!surface)
  {
    // TODO: handle dis is fucked up
  }
  _width = surface->w;
  _height = surface->h;
  // _texture = Texture(renderer, surface);
  SDL_FreeSurface(surface);
}

TextWidget::TextWidget(TextWidget& text_widget)
  : _x(text_widget.x())
  , _y(text_widget.y())
  , _width(text_widget.width())
  , _height(text_widget.height())
  , _text(text_widget.text())
  , _foreground_color(text_widget.foreground_color())
  , _background_color(text_widget.background_color())
{}

const unsigned int& TextWidget::x() const
{
  return _x;
}

const unsigned int& TextWidget::y() const
{
  return _y;
}

const unsigned int& TextWidget::width() const
{
  return _width;
}

const unsigned int& TextWidget::height() const
{
  return _height;
}

const std::string& TextWidget::text() const
{
  return _text;
}

const SDL_Color& TextWidget::foreground_color() const
{
  return _foreground_color;
}

const SDL_Color& TextWidget::background_color() const
{
  return _background_color;
}

unsigned int& TextWidget::x()
{
  return _x;
}

unsigned int& TextWidget::y()
{
  return _y;
}

unsigned int& TextWidget::width()
{
  return _width;
}

unsigned int& TextWidget::height()
{
  return _height;
}

std::string& TextWidget::text()
{
  return _text;
}

void TextWidget::render(const Renderer& renderer, TTF_Font* font) const
{
  Texture texture =
    Texture(renderer,
            TTF_RenderUTF8_Shaded(
              font, _text.c_str(), _foreground_color, _background_color));
  texture.render(renderer, _x, _y);
}