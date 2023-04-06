#include "../include/cursor_widget.hpp"
#include "../include/singleton_renderer.hpp"

CursorWidget::CursorWidget() {}

CursorWidget::~CursorWidget() {}

void CursorWidget::render() const
{
  SingletonRenderer::get_instance()->set_draw_color(this->_background_color);
  SDL_Rect destination_rect{
    static_cast<int>(this->_x),
    static_cast<int>(this->_y),
    static_cast<int>(this->_width),
    static_cast<int>(this->_height),
  };
  SDL_RenderFillRect(SingletonRenderer::get_instance()->renderer(),
                     &destination_rect);
}