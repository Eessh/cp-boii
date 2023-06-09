//
// Created by eessh on 04-05-2023.
//

#ifndef CP_BOII_EDITOR_VIEW_HPP
#define CP_BOII_EDITOR_VIEW_HPP

#include <string>
#include "direct_render.hpp"
#include "font_manager.hpp"
#include "result.hpp"
#include "singleton_renderer.hpp"
#include "text_buffers/vector_buffer/vector_buffer.hpp"
#include "texture_manager.hpp"

class EditorView
{
public:
  EditorView();
  explicit EditorView(const std::string& text);
  explicit EditorView(const std::vector<std::string>& buffer);

  ~EditorView() = default;

  //  Getters
  [[nodiscard]] Result<const int&, std::string> x() const;
  [[nodiscard]] Result<const int&, std::string> y() const;
  [[nodiscard]] Result<const int&, std::string> width() const;
  [[nodiscard]] Result<const int&, std::string> height() const;
  [[nodiscard]] Result<const SDL_Color&, std::string> foreground() const;
  [[nodiscard]] Result<const SDL_Color&, std::string> background() const;
  [[nodiscard]] Result<const SDL_Color&, std::string> active_background() const;
  [[nodiscard]] Result<const SDL_Color&, std::string>
  line_number_foreground() const;
  [[nodiscard]] Result<const SDL_Color&, std::string>
  line_number_background() const;
  [[nodiscard]] Result<const SDL_Color&, std::string>
  line_number_active_foreground() const;
  [[nodiscard]] Result<const SDL_Color&, std::string>
  line_number_active_background() const;
  [[nodiscard]] Result<const SDL_Color&, std::string> selection_color() const;
  [[nodiscard]] Result<bool, std::string> animation_happening() const;

  //  Setters
  Result<bool, std::string> set_x(const int& x);
  Result<bool, std::string> set_y(const int& y);
  Result<bool, std::string> set_width(const int& width);
  Result<bool, std::string> set_height(const int& height);
  Result<bool, std::string> set_foreground(const SDL_Color& foreground);
  Result<bool, std::string> set_background(const SDL_Color& background);
  Result<bool, std::string>
  set_active_background(const SDL_Color& active_background);
  Result<bool, std::string>
  set_line_number_foreground(const SDL_Color& line_number_foreground);
  Result<bool, std::string>
  set_line_number_background(const SDL_Color& line_number_background);
  Result<bool, std::string> set_line_number_active_foreground(
    const SDL_Color& line_number_active_foreground);
  Result<bool, std::string> set_line_number_active_background(
    const SDL_Color& line_number_active_background);
  Result<bool, std::string>
  set_selection_color(const SDL_Color& selection_color);

  //  Loggers
  void log_buffer() const;

  [[nodiscard]] Result<bool, std::string>
  process_sdl_event(const SDL_Event& event);

  [[nodiscard]] Result<bool, std::string> render() const;

private:
  int _x, _y, _width, _height;
  SDL_Color _foreground, _background, _active_background,
    _line_number_foreground, _line_number_background,
    _line_number_active_foreground, _line_number_active_background,
    _selection_color;
  int _scroll_offset_x, _scroll_offset_y;
  int _scrollbar_width, _scrollbar_offset, _scrollbar_y, _scrollbar_height;
  bool _scrollbar_active;
  int _scrollbar_active_instance_x, _scrollbar_active_instance_y;
  float _animation_scroll_offset_x, _animation_scroll_offset_y;
  bool _animation_happening;
  VectorBuffer _buffer;

  int _character_width, _character_height;

  [[nodiscard]] bool point_lies_inside(const int& x, const int& y) const;
  [[nodiscard]] bool point_lies_inside_scrollbar(const int& x,
                                                 const int& y) const;
};

#endif //CP_BOII_EDITOR_VIEW_HPP
