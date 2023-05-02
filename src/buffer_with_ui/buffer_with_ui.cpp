//
// Created by eessh on 02-05-2023.
//

#include "../../include/buffer_with_ui/buffer_with_ui.hpp"

BufferWithUI::BufferWithUI()
: _buffer({""}), _caret_position({-1, 0}), _has_selection(false), _selection({{0, 0}, {0, 0}})
{}

BufferWithUI::BufferWithUI(const std::string& text)
: _buffer({text}), _caret_position({-1, 0}), _has_selection(false), _selection({{0, 0}, {0, 0}})
{}

BufferWithUI::BufferWithUI(const std::vector<std::string>& text)
: _buffer(text), _caret_position({-1, 0}), _has_selection(false), _selection({{0, 0}, {0, 0}})
{}

Result<std::pair<int, int>, std::string> BufferWithUI::caret_position() const
{
  return Ok(_caret_position);
}

Result<bool, std::string> BufferWithUI::has_selection() const
{
  return Ok(_has_selection);
}

Result<std::pair<std::pair<int, int>, std::pair<int, int>>, std::string> BufferWithUI::selection() const
{
  if (!_has_selection) {
    return Error<std::string>("Editor has no selection!");
  }
  return Ok(_selection);
}

Result<std::string, std::string> BufferWithUI::selection_text() const
{
//  TODO: handle dis
  return Ok<std::string>("");
}

Result<bool, std::string> BufferWithUI::set_caret_position(const std::pair<int, int>& position)
{
  if (position.first < -1) {
    return Error<std::string>("First coordinate of caret to set is less than -1!");
  }
  if (position.second < -1) {
    return Error<std::string>("Second coordinate of caret to set is less than -1!");
  }
  if (position.first >= _buffer.size()) {
    return Error<std::string>("First coordinate of caret to set is more than length of buffer!");
  }
  if (position.second >= _buffer[position.second].size()) {
    return Error<std::string>("Second coordinate of caret to set is more than the length of the line in buffer!");
  }
  _caret_position = position;
  return Ok(true);
}

Result<bool, std::string> BufferWithUI::set_selection(const std::pair<int, int>& start, const std::pair<int, int>& end)
{
  if (start.first < 0) {
    return Error<std::string>("First coordinate of selection in start position is less than 0!");
  }
  if (start.second < 0) {
    return Error<std::string>("Second coordinate of selection in start position is less than 0!");
  }
  if (start.first >= _buffer.size()) {
    return Error<std::string>("First coordinate of selection in start position is more than length of buffer!");
  }
  if (start.second >= _buffer[start.first].size()) {
    return Error<std::string>("Second coordinate of selection in start position is more than length of the line in buffer!");
  }
  if (end.first < 0) {
    return Error<std::string>("First coordinate of selection in end position is less than 0!");
  }
  if (end.second < 0) {
    return Error<std::string>("Second coordinate of selection in end position is less than 0!");
  }
  if (end.first >= _buffer.size()) {
    return Error<std::string>("First coordinate of selection in end position is more than length of buffer!");
  }
  if (end.second >= _buffer[end.first].size()) {
    return Error<std::string>("Second coordinate of selection in end position is more than length of the line in buffer!");
  }
  _has_selection = true;
  _selection = {start, end};
  return Ok(true);
}

void BufferWithUI::execute_caret_command(const BufferCaretCommand& command)
{
  switch(command)
  {
  case BufferCaretCommand::MOVE_LEFT: {
    if (_caret_position.second == -1) {
      return;
    }
    _caret_position.second -= 1;
    break;
  }
  case BufferCaretCommand::MOVE_RIGHT: {
    if (_caret_position.second == _buffer[_caret_position.first].size()-1) {
      return;
    }
    _caret_position.second += 1;
    break;
  }
  case BufferCaretCommand::MOVE_UP: {
    if (_caret_position.first == 0) {
      return;
    }
    _caret_position.first -= 1;
    break;
  }
  case BufferCaretCommand::MOVE_DOWN: {
    if (_caret_position.first == _buffer.size()-1) {
      return;
    }
    _caret_position.first += 1;
    break;
  }
  case BufferCaretCommand::MOVE_TO_LINE_STARTING: {
    _caret_position.second = 0;
    break;
  }
  case BufferCaretCommand::MOVE_TO_LINE_ENDING: {
    _caret_position.second = (int)_buffer[_caret_position.first].size()-1;
    break;
  }
  case BufferCaretCommand::MOVE_TO_BUFFER_STARTING: {
    _caret_position.first = 0;
    break;
  }
  case BufferCaretCommand::MOVE_TO_BUFFER_ENDING: {
    _caret_position.first = (int)_buffer.size()-1;
    break;
  }
  default:
    break;
  }
}