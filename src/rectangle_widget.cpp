#include "../include/rectangle_widget.hpp"
#include <SDL2/SDL_render.h>
#include "../include/singleton_renderer.hpp"

RectangleWidget::RectangleWidget() {}

RectangleWidget::~RectangleWidget() {}

const RectangleStyle& RectangleWidget::style() const {
  return _style;
}

RectangleStyle& RectangleWidget::style() {
  return _style;
}

void RectangleWidget::process_sdl_event(const SDL_Event &event) {}

void RectangleWidget::render() const {
  SingletonRenderer::get_instance()->set_draw_color(this->_background_color);
  SDL_Rect destination_rect {
    static_cast<int>(this->_x),
    static_cast<int>(this->_y),
    static_cast<int>(this->_width),
    static_cast<int>(this->_height)
  };
  if (_style == RectangleStyle::FILLED) {
    SDL_RenderFillRect(SingletonRenderer::get_instance()->renderer(), &destination_rect);
  }
  else {
    SDL_RenderDrawRect(SingletonRenderer::get_instance()->renderer(), &destination_rect);
  }
}