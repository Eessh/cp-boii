#include "../include/string_widget.hpp"
#include "../include/font_manager.hpp"
#include "../include/singleton_renderer.hpp"
#include "../log-boii/log_boii.h"

StringWidget::StringWidget(const std::string& text) : _text(text)
// , _texture(nullptr)
{
  // SDL_Surface* text_surface =
  //   TTF_RenderText_Shaded(SingletonRenderer::get_instance()->font(),
  //                         text.c_str(),
  //                         this->_foreground_color,
  //                         this->_background_color);
  // if(!text_surface)
  // {
  //   log_error("Error while creating surface for text: %s", TTF_GetError());
  //   // TODO: handle dis
  // }
  // _texture = SDL_CreateTextureFromSurface(
  //   SingletonRenderer::get_instance()->renderer(), text_surface);
  // if(!_texture)
  // {
  //   log_error("Error while creating texture from surface: %s", SDL_GetError());
  //   // TODO: handle dis
  // }
  // this->_width = text_surface->w;
  // this->_height = text_surface->h;
  // SDL_FreeSurface(text_surface);

  std::pair<unsigned int, unsigned int> text_dimensions =
    FontManager::get_instance()->get_text_dimensions(text);
  this->_width = text_dimensions.first;
  this->_height = text_dimensions.second;
}

StringWidget::~StringWidget()
{
  // SDL_DestroyTexture(_texture);
}

const std::string& StringWidget::text() const
{
  return _text;
}

std::string& StringWidget::text()
{
  return _text;
}

void StringWidget::process_event(const SDL_Event& event)
{
  switch(event.type)
  {
  // case SDL_MOUSEMOTION:{
  //   if (this->_x<=event.motion.x && event.motion.x<=this->_x+this->_width && this->_y<=event.motion.y && event.motion.y<=this->_y+this->_width) {
  //     // Mouse inside widget
  //     // if (_text == "Madda Gudu") {
  //     //   _text = "Minge ra pumka";
  //     // }
  //     // else {
  //     //   _text = "Madda Gudu";
  //     // }
  //     // update_texture();
  //   }
  //   break;
  // }
  default: {
    break;
  }
  }
}

void StringWidget::render() const
{
  SingletonRenderer::get_instance()->set_draw_color(this->_foreground_color);
  int painter_x = this->_x, painter_y = this->_y;
  for(const char& c : _text)
  {
    std::pair<const unsigned int&, const unsigned int&> char_dimensions =
      TextureManager::get_instance()->get_alphabet_char_texture_dimensions(c);
    SDL_Rect char_destination_rect{painter_x,
                                   painter_y,
                                   static_cast<int>(char_dimensions.first),
                                   static_cast<int>(char_dimensions.second)};
    SDL_RenderCopy(SingletonRenderer::get_instance()->renderer(),
                   TextureManager::get_instance()->get_alphabet_char_texture(c),
                   nullptr,
                   &char_destination_rect);
    painter_x += char_dimensions.first;
  }
  // SDL_Rect destination_rect{
  //   static_cast<int>(this->_x),
  //   static_cast<int>(this->_y),
  //   static_cast<int>(this->_width),
  //   static_cast<int>(this->_height),
  // };
  // SDL_RenderCopy(SingletonRenderer::get_instance()->renderer(),
  //                _texture,
  //                nullptr,
  //                &destination_rect);
  SingletonRenderer::get_instance()->set_draw_color({0, 0, 0, 0});
}

// void StringWidget::update_texture()
// {
//   SDL_DestroyTexture(_texture);
//   SDL_Surface* text_surface =
//     TTF_RenderText_Shaded(SingletonRenderer::get_instance()->font(),
//                           _text.c_str(),
//                           this->_foreground_color,
//                           this->_background_color);
//   if(!text_surface)
//   {
//     log_error("Error while updating surface for text: %s", TTF_GetError());
//     // TODO: handle dis
//   }
//   _texture = SDL_CreateTextureFromSurface(
//     SingletonRenderer::get_instance()->renderer(), text_surface);
//   if(!_texture)
//   {
//     log_error("Error while updating texture from surface: %s", SDL_GetError());
//     // TODO: handle dis
//   }
//   this->_width = text_surface->w;
//   this->_height = text_surface->h;
//   SDL_FreeSurface(text_surface);
// }