//
// Created by eessh on 04-05-2023.
//

#include "../include/editor_view.hpp"
#include <iostream>
#include "../include/cursor_manager.hpp"
#include "../log-boii/log_boii.h"

EditorView::EditorView()
  : _x(0)
  , _y(0)
  , _width(0)
  , _height(0)
  , _foreground({255, 255, 255, 255})
  , _background({0, 0, 0, 255})
  , _active_background({0, 0, 0, 255})
  , _line_number_foreground({255, 255, 255, 255})
  , _line_number_background({0, 0, 0, 255})
  , _line_number_active_foreground({255, 255, 255, 255})
  , _line_number_active_background({0, 0, 0, 0})
  , _scroll_offset_x(0)
  , _scroll_offset_y(0)
  , _scrollbar_width(10)
  , _scrollbar_offset(2)
  , _animation_scroll_offset_x(0.0f)
  , _animation_scroll_offset_y(0.0f)
  , _animation_happening(false)
  , _buffer("")
{
  std::pair<const unsigned int&, const unsigned int&> character_dimensions =
    TextureManager::get_instance()->get_alphabet_char_texture_dimensions('a');
  _character_width = (int)character_dimensions.first;
  _character_height = (int)character_dimensions.second;
}

EditorView::EditorView(const std::string& text)
  : _x(0)
  , _y(0)
  , _width(0)
  , _height(0)
  , _foreground({255, 255, 255, 255})
  , _background({0, 0, 0, 255})
  , _active_background({0, 0, 0, 255})
  , _line_number_foreground({255, 255, 255, 255})
  , _line_number_background({0, 0, 0, 255})
  , _line_number_active_foreground({255, 255, 255, 255})
  , _line_number_active_background({0, 0, 0, 0})
  , _scroll_offset_x(0)
  , _scroll_offset_y(0)
  , _scrollbar_width(10)
  , _scrollbar_offset(2)
  , _animation_scroll_offset_x(0.0f)
  , _animation_scroll_offset_y(0.0f)
  , _animation_happening(false)
  , _buffer(text)
{
  std::pair<const unsigned int&, const unsigned int&> character_dimensions =
    TextureManager::get_instance()->get_alphabet_char_texture_dimensions('a');
  _character_width = (int)character_dimensions.first;
  _character_height = (int)character_dimensions.second;
}

EditorView::EditorView(const std::vector<std::string>& buffer)
  : _x(0)
  , _y(0)
  , _width(0)
  , _height(0)
  , _foreground({255, 255, 255, 255})
  , _background({0, 0, 0, 255})
  , _active_background({0, 0, 0, 255})
  , _line_number_foreground({255, 255, 255, 255})
  , _line_number_background({0, 0, 0, 255})
  , _line_number_active_foreground({255, 255, 255, 255})
  , _line_number_active_background({0, 0, 0, 0})
  , _scroll_offset_x(0)
  , _scroll_offset_y(0)
  , _scrollbar_width(10)
  , _scrollbar_offset(2)
  , _animation_scroll_offset_x(0.0f)
  , _animation_scroll_offset_y(0.0f)
  , _animation_happening(false)
  , _buffer(buffer)
{
  std::pair<const unsigned int&, const unsigned int&> character_dimensions =
    TextureManager::get_instance()->get_alphabet_char_texture_dimensions('a');
  _character_width = (int)character_dimensions.first;
  _character_height = (int)character_dimensions.second;
#ifdef DEBUG
  log_debug("Font character width, height: %d, %d",
            _character_width,
            _character_height);
#endif
}

Result<const int&, std::string> EditorView::x() const
{
  return Ok<const int&>(_x);
}

Result<const int&, std::string> EditorView::y() const
{
  return Ok<const int&>(_y);
}

Result<const int&, std::string> EditorView::width() const
{
  return Ok<const int&>(_width);
}

Result<const int&, std::string> EditorView::height() const
{
  return Ok<const int&>(_height);
}

Result<const SDL_Color&, std::string> EditorView::foreground() const
{
  return Ok<const SDL_Color&>(_foreground);
}

Result<const SDL_Color&, std::string> EditorView::background() const
{
  return Ok<const SDL_Color&>(_background);
}

Result<const SDL_Color&, std::string> EditorView::active_background() const
{
  return Ok<const SDL_Color&>(_active_background);
}

Result<const SDL_Color&, std::string> EditorView::line_number_foreground() const
{
  return Ok<const SDL_Color&>(_line_number_foreground);
}

Result<const SDL_Color&, std::string> EditorView::line_number_background() const
{
  return Ok<const SDL_Color&>(_line_number_background);
}

Result<const SDL_Color&, std::string>
EditorView::line_number_active_foreground() const
{
  return Ok<const SDL_Color&>(_line_number_active_foreground);
}

Result<const SDL_Color&, std::string>
EditorView::line_number_active_background() const
{
  return Ok<const SDL_Color&>(_line_number_active_background);
}

Result<bool, std::string> EditorView::animation_happening() const
{
  return Ok(_animation_happening);
}

Result<bool, std::string> EditorView::set_x(const int& x)
{
  _x = x;
  return Ok(true);
}

Result<bool, std::string> EditorView::set_y(const int& y)
{
  return Ok(true);
}

Result<bool, std::string> EditorView::set_width(const int& width)
{
  _width = width;
  return Ok(true);
}

Result<bool, std::string> EditorView::set_height(const int& height)
{
  _height = height;
  return Ok(true);
}

Result<bool, std::string>
EditorView::set_foreground(const SDL_Color& foreground)
{
  _foreground = foreground;
  return Ok(true);
}

Result<bool, std::string>
EditorView::set_background(const SDL_Color& background)
{
  _background = background;
  return Ok(true);
}

Result<bool, std::string>
EditorView::set_active_background(const SDL_Color& active_background)
{
  _active_background = active_background;
  return Ok(true);
}

Result<bool, std::string>
EditorView::set_line_number_foreground(const SDL_Color& line_number_foreground)
{
  _line_number_foreground = line_number_foreground;
  return Ok(true);
}

Result<bool, std::string>
EditorView::set_line_number_background(const SDL_Color& line_number_background)
{
  _line_number_background = line_number_background;
  return Ok(true);
}

Result<bool, std::string> EditorView::set_line_number_active_foreground(
  const SDL_Color& line_number_active_foreground)
{
  _line_number_active_foreground = line_number_active_foreground;
  return Ok(true);
}

Result<bool, std::string> EditorView::set_line_number_active_background(
  const SDL_Color& line_number_active_background)
{
  _line_number_active_background = line_number_active_background;
  return Ok(true);
}

void EditorView::log_buffer() const
{
  std::cout << "Buffer: {\n";
  for(int i = 0; i < _buffer.size(); i++)
  {
    std::cout << _buffer.get_line(i).ok_value() << "\n";
  }
  std::cout << "}\n";
}

Result<bool, std::string> EditorView::process_sdl_event(const SDL_Event& event)
{
  switch(event.type)
  {
  case SDL_WINDOWEVENT: {
    if(event.window.event == SDL_WINDOWEVENT_RESIZED)
    {
      _width = event.window.data1;
      _height = event.window.data2;
    }
    return Ok(true);
  }
  case SDL_MOUSEMOTION: {
    if(!point_lies_inside(event.motion.x, event.motion.y))
    {
      return Ok(false);
    }
    int line_numbers_view_width =
      static_cast<int>(
        std::string(" " + std::to_string(_buffer.size()) + " ").size()) *
      _character_width;
    if(event.motion.x <= line_numbers_view_width)
    {
      CursorManager::get_instance()->set_arrow();
    }
    else
    {
      CursorManager::get_instance()->set_ibeam();
    }
    break;
  }
  case SDL_MOUSEBUTTONDOWN: {
    if(!point_lies_inside(event.button.x, event.button.y))
    {
      return Ok(false);
    }
    if(event.button.button == SDL_BUTTON_LEFT)
    {
      //      left click
      int line_numbers_view_width =
        static_cast<int>(
          std::string(" " + std::to_string(_buffer.size()) + " ").size()) *
        _character_width;
      int line_number =
        (event.button.y/_character_height) - _scroll_offset_y/_character_height;
      if(event.button.x <= line_numbers_view_width)
      {
        _buffer.set_cursor_coords(line_number, -1);
        return Ok(true);
      }
      int column =
        (event.button.x - line_numbers_view_width) / _character_width;
      int max_column_for_line_number =
        static_cast<int>(_buffer.get_line(line_number).ok_value().size());
      _buffer.set_cursor_coords(line_number,
                                max_column_for_line_number < column
                                  ? max_column_for_line_number - 1
                                  : column - 1);
    }
    else if(event.button.button == SDL_BUTTON_RIGHT)
    {
      //      right click
    }
    else if(event.button.button == SDL_BUTTON_MIDDLE)
    {
      //      middle click
    }
    else
    {
      return Ok(false);
    }
    return Ok(true);
  }
  case SDL_KEYDOWN: {
#ifdef DEBUG
    log_debug("Key code: %d, scancode: %d, name: %s", event.key.keysym.sym, event.key.keysym.scancode, SDL_GetKeyName(event.key.keysym.sym));
#endif
    if(event.key.keysym.sym == SDLK_UP)
    {
      _buffer.execute_command(Command::MOVE_CURSOR_UP);
      std::pair<int, int> cursor_coords =
        _buffer.get_cursor_coords().ok_value();
      if(cursor_coords.first < -_scroll_offset_y)
      {
        _scroll_offset_y += 1;
      }
      if(cursor_coords.first + _scroll_offset_y < 1)
      {
        _scroll_offset_y = -cursor_coords.first;
      }
    }
    else if(event.key.keysym.sym == SDLK_DOWN)
    {
      _buffer.execute_command(Command::MOVE_CURSOR_DOWN);
      std::pair<int, int> cursor_coords =
        _buffer.get_cursor_coords().ok_value();
      int lines_fitting = _height / _character_height;
      if(cursor_coords.first + _scroll_offset_y > lines_fitting - 1)
      {
        _scroll_offset_y -= 1;
      }
      if(cursor_coords.first + _scroll_offset_y < 1)
      {
        _scroll_offset_y = -cursor_coords.first;
      }
    }
    else
    {
      //      TODO: handle dis
      const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);
      if (keyboard_state[SDL_SCANCODE_LEFT]) {
        if (keyboard_state[SDL_SCANCODE_LCTRL] || keyboard_state[SDL_SCANCODE_RCTRL]) {
          _buffer.execute_command(Command::MOVE_CURSOR_TO_HOME);
        }
        else {
          _buffer.execute_command(Command::MOVE_CURSOR_BACK);
        }
      }
      else if (keyboard_state[SDL_SCANCODE_RIGHT]) {
        if (keyboard_state[SDL_SCANCODE_LCTRL] || keyboard_state[SDL_SCANCODE_RCTRL]) {
          _buffer.execute_command(Command::MOVE_CURSOR_TO_END);
        }
        else {
          _buffer.execute_command(Command::MOVE_CURSOR_FORWARD);
        }
      }
      else {
//        TODO
      }
    }
    return Ok(true);
  }
  case SDL_MOUSEWHEEL: {
    if(!point_lies_inside(event.wheel.mouseX, event.wheel.mouseY))
    {
      return Ok(false);
    }
    if(event.wheel.y > 0)
    {
      //      Scrolling down
#ifdef DEBUG
      log_info("Scrolling down, y: %d", event.wheel.y);
#endif
      _scroll_offset_y += abs(event.wheel.y)*_character_height;
      if(_scroll_offset_y > 0)
      {
        _scroll_offset_y = 0;
      }
    }
    if(event.wheel.y < 0)
    {
      //      Scroll up
#ifdef DEBUG
      log_info("Scrolling up, y: %d", event.wheel.y);
#endif
      _scroll_offset_y -= abs(event.wheel.y)*_character_height;
      int buffer_height = (int)(_character_height * _buffer.size());
//      if(_scroll_offset_y * _character_height <= -buffer_height + _height)
//      {
//        _scroll_offset_y = -buffer_height / _character_height +
//                           (_height / _character_height) + 1;
//      }
      if (_scroll_offset_y-_height<-buffer_height) {
        _scroll_offset_y = -buffer_height+_height;
      }
    }
    return Ok(true);
  }
  }
  return Ok(false);
}

Result<bool, std::string> EditorView::render() const
{
  SingletonRenderer::get_instance()->set_clip_rect({_x, _y, _width, _height});

  //  TODO: Shift functionality for drawing lines over here from DirectRender::render_line_view()

//  int painter_x = _x, painter_y = _y + _character_height * _scroll_offset_y;
  int painter_x = _x, painter_y = _y + _scroll_offset_y;
  unsigned int buffer_line_to_render = 0;
  while(painter_y < 0 && abs(painter_y) >= _character_height &&
        buffer_line_to_render < _buffer.size())
  {
    buffer_line_to_render += 1;
    painter_y += _character_height;
  }
  while(buffer_line_to_render < _buffer.size() && painter_y < _height)
  {
    Result<bool, std::string> line_render_result =
      DirectRender::render_line_view(
        painter_x,
        painter_y,
        _width,
        _buffer.get_line(buffer_line_to_render).ok_value(),
        static_cast<int>(buffer_line_to_render),
        _buffer.size(),
        _buffer.get_cursor_coords().ok_value().first == buffer_line_to_render,
        _foreground,
        _background,
        _active_background,
        _line_number_foreground,
        _line_number_background,
        _line_number_active_foreground,
        _line_number_active_background);
    if(line_render_result.error())
    {
      return line_render_result;
    }
    buffer_line_to_render += 1;
    painter_y += _character_height;
  }

  //  Drawing cursor
  std::string max_line_number_str = std::to_string(_buffer.size());
  max_line_number_str.insert(max_line_number_str.begin(), ' ');
  max_line_number_str.push_back(' ');
  std::pair<int, int> cursor_coords = _buffer.get_cursor_coords().ok_value();
  auto _ = DirectRender::render_filled_rectangle(
    (static_cast<int>(max_line_number_str.length()) + _scroll_offset_x +
     cursor_coords.second + 1) *
      _character_width,
    (_scroll_offset_y/_character_height + cursor_coords.first) * _character_height + _scroll_offset_y%_character_height,
    2,
    _character_height,
    _foreground);
  if(_.error())
  {
    return _;
  }

  //  Drawing scrollbar
  float height_ratio = static_cast<float>(_height) /
                       static_cast<float>(_buffer.size() * _character_height);
  int scrollbar_height =
    static_cast<int>(height_ratio * static_cast<float>(_height));
  int scrollbar_y =
    static_cast<int>(static_cast<float>(-_scroll_offset_y) * height_ratio);
  //  _ = DirectRender::render_filled_semicircle(
  //    _x + _width - 8,
  //    _y + 5,
  //    5,
  //    {.r = _foreground.r, .g = _foreground.g, .b = _foreground.b, .a = 100});
  //  if (_.error()) {
  //    return _;
  //  }
  _ = DirectRender::render_filled_rectangle(
    _x + _width - _scrollbar_width - _scrollbar_offset,
    scrollbar_y,
    10,
    scrollbar_height,
    {.r = _foreground.r, .g = _foreground.g, .b = _foreground.b, .a = 100});
  if(_.error())
  {
    return _;
  }
  //  _ = DirectRender::render_filled_inverted_semicircle(_x+_width-7, _y+5+100, 5, {.r = _foreground.r, .g = _foreground.g, .b = _foreground.b, .a = 100});
  //  if (_.error()) {
  //    return _;
  //  }
  //  SingletonRenderer::get_instance()->remove_clip_rect();

  return Ok(true);
}

bool EditorView::point_lies_inside(const int& x, const int& y) const
{
  return _x <= x && x <= (_x + _width) && _y <= y && y <= (_y + _height);
}
