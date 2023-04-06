#include "../include/tokenizable_text_widget.hpp"
#include "../include/texture_manager.hpp"
#include "../include/font_manager.hpp"
#include "../include/singleton_renderer.hpp"

TokenizableTextWidget::TokenizableTextWidget(const std::string& text)
: _text(text)
{
  std::pair<unsigned int, unsigned int> text_dimensions =
    FontManager::get_instance()->get_text_dimensions(text);
  this->_width = text_dimensions.first;
  this->_height = text_dimensions.second;
}

TokenizableTextWidget::~TokenizableTextWidget() {}

const std::string& TokenizableTextWidget::text() const {
  return _text;
}

std::string& TokenizableTextWidget::text() {
  return _text;
}

void TokenizableTextWidget::process_sdl_event(const SDL_Event &event) {}

void TokenizableTextWidget::render() const {
  // Do the parsing stuff
  // get tokens with respective colors
  // render them

  // for the time being
  // rendering whole string in one color
  SDL_Texture* text_tetxure = TextureManager::get_instance()->get_colored_string_texture(_text, this->_foreground_color);
  SDL_Rect destination_rect {
    static_cast<int>(this->_x),
    static_cast<int>(this->_y),
    static_cast<int>(this->_width),
    static_cast<int>(this->_height)
  };
  SDL_RenderCopy(SingletonRenderer::get_instance()->renderer(), text_tetxure, nullptr, &destination_rect);
  SDL_DestroyTexture(text_tetxure);
}