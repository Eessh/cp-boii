#include "../include/vertical_view_widget.hpp"
#include "../include/global_state.hpp"
#include "../include/singleton_renderer.hpp"
#include "../log-boii/log_boii.h"

VerticalViewWidget::VerticalViewWidget()
  : _padding_x(0), _padding_y(0), _scroll_offset_x(0), _scroll_offset_y(0)
{}

VerticalViewWidget::~VerticalViewWidget() {}

void VerticalViewWidget::process_event(const SDL_Event& event)
{
  switch(event.type)
  {
  case SDL_MOUSEMOTION: {
    // if(point_lies_inside(event.motion.x, event.motion.y))
    // {
    //   this->_background_color = {128, 128, 128, 255};
    // }
    // else
    // {
    //   this->_background_color = {200, 200, 200, 255};
    // }
    break;
  }
  case SDL_WINDOWEVENT: {
    if(event.window.event == SDL_WINDOWEVENT_RESIZED)
    {
      this->_width = event.window.data1;
      this->_height = event.window.data2;
    }
    break;
  }
  case SDL_MOUSEWHEEL: {
    if(!point_lies_inside(event.wheel.mouseX, event.wheel.mouseY))
    {
      return;
    }
    if(event.wheel.y > 0)
    {
      // scroll down
      _scroll_offset_y += 10 * event.wheel.y;
      if(_scroll_offset_y > 0)
      {
        _scroll_offset_y = 0;
      }
      // log_debug("Scroll down, offset = %d, preciseY: %f", _scroll_offset_y, event.wheel.preciseX);
    }
    if(event.wheel.y < 0)
    {
      // scroll up
      _scroll_offset_y += 10 * event.wheel.y;
      unsigned int children_height = 0;
      for(const BaseWidget* child : this->_children)
      {
        children_height += child->height();
      }
      children_height -= this->_children.back()->height();
      if(abs(_scroll_offset_y) > children_height)
      {
        _scroll_offset_y = -children_height;
      }
      // log_debug("Scroll up, offset = %d, preciseY: %f", _scroll_offset_y, event.wheel.preciseX);
    }
    if(event.wheel.x > 0)
    {
      // scroll right
      // _scroll_offset_x += 1600 * GlobalState::get_instance()->delta_time() * event.wheel.x;
      _scroll_offset_x += 10 * event.wheel.x;
      unsigned int max_child_width = 0;
      for(const BaseWidget* child : this->_children)
      {
        max_child_width = std::max(max_child_width, child->width());
      }
      if(max_child_width <= this->_width)
      {
        _scroll_offset_x = 0;
      }
      else if(abs(_scroll_offset_x) > max_child_width - this->_width)
      {
        _scroll_offset_x = max_child_width - this->_width;
      }
      // log_debug("Scroll right, offset = %d", _scroll_offset_x);
    }
    if(event.wheel.x < 0)
    {
      // scroll left
      _scroll_offset_x += 10 * event.wheel.x;
      if(_scroll_offset_x < 0)
      {
        _scroll_offset_x = 0;
      }
      // log_debug("Scroll left, offset = %d", _scroll_offset_x);
    }
    break;
  }
  // case SDL_MOUSEWHEEL: {
  //   if(!point_lies_inside(event.wheel.mouseX, event.wheel.mouseY))
  //   {
  //     return;
  //   }

  //   break;
  // }
  case SDL_MULTIGESTURE: {
    if(!point_lies_inside(event.wheel.mouseX, event.wheel.mouseY))
    {
      return;
    }
    // TODO: handle scrolling using multigestures
    // for more cheeewesey butttery scrolling
    if(event.mgesture.numFingers == 2)
    {
      if(!_is_scrolling)
      {
        _is_scrolling = true;
        _scroll_offset_y_prev = event.mgesture.y;
      }
      else
      {
        double dy = event.mgesture.y - _scroll_offset_y_prev;
        _scroll_acceleration = _scroll_sensitivity * dy;
        _scroll_offset_y_prev = event.mgesture.y;
        _is_scrolling = true;
      }

      if(_scroll_acceleration > 0)
      {
        _scroll_acceleration -= _scroll_friction;
      }
      else if(_scroll_acceleration < 0)
      {
        _scroll_acceleration += _scroll_friction;
      }
      if(abs(_scroll_acceleration < 0.00005))
      {
        _scroll_acceleration = 0;
      }
      _scroll_offset_y += _scroll_sensitivity * _scroll_acceleration;

      // Scrolling bounds
      if(_scroll_offset_y > 0)
      {
        _scroll_offset_y = 0;
      }
    }
    break;
  }
  case SDL_FINGERDOWN: {
    _is_scrolling = false;
    break;
  }
  default: {
    break;
  }
  }
  for(BaseWidget* child : this->_children)
  {
    child->process_event(event);
  }
}

void VerticalViewWidget::render() const
{
  // Viewport of this widget
  SDL_Rect destination_rect{
    static_cast<int>(_x),
    static_cast<int>(_y),
    static_cast<int>(_width + 2 * _padding_x),
    static_cast<int>(_height + 2 * _padding_y),
  };

  // Setting renderer configs
  SingletonRenderer::get_instance()->set_clip_rect(destination_rect);
  SingletonRenderer::get_instance()->set_draw_color(this->_background_color);

  // painter coordinates
  int painter_x = this->_x + _padding_x;
  int painter_y = this->_y + _padding_y;

  // TODO: handle scrolling offset
  // handle using scroll accleration & friction for smooth scrolling
  // painter_x += _scroll_offset_x;
  // painter_y += _scroll_offset_y;

  unsigned int child_index = 0;
  int temp_scroll_offset_y = _scroll_offset_y;
  while(child_index < this->_children.size())
  {
    if(this->_children[child_index]->height() < abs(temp_scroll_offset_y))
    {
      // child height is less than scroll offset
      // so subtracting child height from scroll offset
      // log_debug("inside if: height, temp_offset = %d, %d", this->_children[child_index]->height(), temp_scroll_offset_y);
      temp_scroll_offset_y += this->_children[child_index]->height();
    }
    else
    {
      // child height is greater than scroll offset
      // so stopping, leaving child for clipped rendering
      break;
    }
    child_index++;
  }
  // log_debug("Child index after filtering: %d", child_index);

  // Rendering this widget
  SDL_RenderFillRect(SingletonRenderer::get_instance()->renderer(),
                     &destination_rect);

  painter_x -= _scroll_offset_x;
  painter_y += temp_scroll_offset_y;
  temp_scroll_offset_y = 0;
  while(child_index < this->_children.size())
  {
    // be careful with this comparison
    // between int & unsigned int
    // fucked up my whole day
    // worked when converted the unsigned int to int
    // as it is known, there would be any buffer overflow
    if(painter_y > (int)(this->_y + 2 * _padding_y + this->_height))
    {
      // log_debug("Painter exceeded viewport: y, viewport_y = %d, %d", painter_y, this->_y + 2 * _padding_y + this->_height);
      break;
    }
    this->_children[child_index]->x() = painter_x;
    this->_children[child_index]->y() = painter_y;
    this->_children[child_index]->render();
    painter_y += this->_children[child_index]->height();
    // log_debug("after rendering painter_y: %d", painter_y);
    child_index++;
  }

  // Clearing renderer configs
  SingletonRenderer::get_instance()->remove_clip_rect();
  SingletonRenderer::get_instance()->set_draw_color({0, 0, 0, 0});
}

bool VerticalViewWidget::point_lies_inside(unsigned int x, unsigned int y) const
{
  return this->_x <= x && x <= this->_x + 2 * _padding_x + this->_width &&
         this->_y <= y && y <= this->_y + 2 * _padding_y + this->_height;
}