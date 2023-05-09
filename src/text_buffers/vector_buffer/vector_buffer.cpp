#include "../../../include/text_buffers/vector_buffer/vector_buffer.hpp"
#include <stdexcept>

VectorBuffer::VectorBuffer()
: _cursor_row(0), _cursor_col(-1)
{
  _buffer.emplace_back("");
}

VectorBuffer::VectorBuffer(const std::string& str)
: _cursor_row(0), _cursor_col(-1)
{
  _buffer.push_back(str);
}

VectorBuffer::VectorBuffer(const std::vector<std::string>& buffer)
: _cursor_row(0), _cursor_col(-1)
{
  _buffer = buffer;
}

Result<std::pair<int, int>, std::string> VectorBuffer::get_cursor_coords() const {
  return Ok<std::pair<int, int>>({_cursor_row, _cursor_col});
}

Result<const std::string&, std::string> VectorBuffer::get_line(const unsigned int& line_number) const {
  if (line_number < 0 || line_number >= _buffer.size()) {
    return Error<std::string>("Line number out of range!");
  }
  return Ok<const std::string&>(_buffer[line_number]);
}

bool VectorBuffer::has_selection() const
{
  return _has_selection;
}

Result<const std::pair<std::pair<int, int>, std::pair<int, int>>&, std::string> VectorBuffer::get_selection() const
{
  if (!_has_selection) {
    return Error<std::string>("Buffer has no selection!");
  }
  if (_selection.first.first < _selection.second.first) {
    return Ok<const std::pair<std::pair<int, int>, std::pair<int, int>>&>(_selection);
  }
  else if (_selection.first.first == _selection.second.first) {
    if (_selection.first.second < _selection.second.second) {
      return Ok<const std::pair<std::pair<int, int>, std::pair<int, int>>&>(_selection);
    }
    return Ok<const std::pair<std::pair<int, int>, std::pair<int, int>>&>({_selection.second, _selection.first});
  }
  return Ok<const std::pair<std::pair<int, int>, std::pair<int, int>>&>(
    {_selection.second, _selection.first});
}

std::string VectorBuffer::get_line_unsafe(const unsigned int& line_number) const
{
  return _buffer[line_number];
}

Result<const std::vector<std::string>&, std::string> VectorBuffer::get_buffer() const {
  return Ok<const std::vector<std::string>&>(_buffer);
}

int VectorBuffer::size() const
{
  return (int)_buffer.size();
}

Result<bool, std::string> VectorBuffer::set_cursor_coords(const int& row, const int& column)
{
  _cursor_row = row;
  _cursor_col = column;
  return Ok(true);
}

Result<bool, std::string> VectorBuffer::set_selection(const std::pair<std::pair<int, int>, std::pair<int, int>>& selection)
{
  if (selection.first.first < 0 || selection.first.first > static_cast<int>(_buffer.size())) {
    return Error<std::string>("Selection starting point row is out of bounds!");
  }
  if (selection.second.first < 0 || selection.second.first > static_cast<int>(_buffer.size())) {
    return Error<std::string>("Selection ending point row is out of bounds!");
  }
  if (selection.first.second < -1 || selection.first.second >= static_cast<int>(_buffer[selection.first.first].size())) {
    return Error<std::string>("Selection starting point column is out of bounds!");
  }
  if (selection.second.second < -1 || selection.second.second >= static_cast<int>(_buffer[selection.second.first].size())) {
    return Error<std::string>("Selection ending point column is out of bounds!");
  }
  _has_selection = true;
  _selection = selection;
  return Ok(true);
}

Result<bool, std::string> VectorBuffer::insert_char(const char& character) {
  if (_cursor_col == _buffer[_cursor_row].size()-1) {
    // cursor at end of line
    // so just pushback the character
    _buffer[_cursor_row].push_back(character);
  }
  else {
    // cursor in middle of line
    _buffer[_cursor_row].insert(_buffer[_cursor_row].begin()+_cursor_col+1, character);
  }
  _cursor_col++;
  return Ok(true);
}

Result<bool, std::string> VectorBuffer::insert_string(const std::string& str) {
  // if we encounter '\n' character in str
  // we need to create a new line and insert
  // the remaining string into it
  // so we need to iterate str, instead of directly inserting
  for (const char& character: str) {
    if (character == '\n') {
      // TODO: handle dis
      // cursor somewhere, but not at last line
      // so need to insert a new line between
      // the current line, and next line
      // and copy the remaining string to the right of cursor
      // to new line
      std::string remaining_string_to_right = _buffer[_cursor_row].substr(_cursor_col+1);
      _buffer.insert(_buffer.begin()+_cursor_row+1, remaining_string_to_right);
      _cursor_row++;
      _cursor_col = -1;
    }
    else {
      _buffer[_cursor_row].insert(_buffer[_cursor_row].begin()+_cursor_col+1, character);
      _cursor_col++;
    }
  }
  return Ok(true);
}

void VectorBuffer::execute_command(const Command& command, const std::string& insert_str) {
  switch (command)
  {
  case Command::BACKSPACE: {
    if (_cursor_col == -1) {
      return;
    }
    // erasing character before cursor
    _buffer[_cursor_row].erase(_buffer[_cursor_row].begin()+_cursor_col);
    _cursor_col--;
    break;
  }
  case Command::ENTER: {
    // cursor somewhere, but not at last line
    // so need to insert a new line between
    // the current line, and next line
    // and copy the remaining string to the right of cursor
    // to new line
    std::string remaining_string_to_right = _buffer[_cursor_row].substr(_cursor_col+1);
    _buffer.insert(_buffer.begin()+_cursor_row+1, remaining_string_to_right);
    _cursor_row++;
    _cursor_col = -1;
    break;
  }
  case Command::INSERT_CHAR: {
    // if (_cursor_col == _buffer[_cursor_row].size()-1) {
    //   // cursor at end of line
    //   // just pushback the string
    // }
    break;
  }
  case Command::INSERT_STRING: {
    break;
  }
  case Command::NEW_LINE: {
    if (_cursor_row == _buffer.size()-1) {
      // cursor at last line
      // so need to create a new line
      // and place cursor at the start
      _buffer.emplace_back("");
      _cursor_row++;
      _cursor_col = -1;
    }
    else {
      // cursor somewhere, but not at last line
      // so need to insert a new line between
      // the current line, and next line
      _buffer.insert(_buffer.begin()+_cursor_row+1, "");
      _cursor_row++;
      _cursor_col = -1;
    }
    break;
  }
  case Command::MOVE_CURSOR_BACK: {
    if (_cursor_col == -1) {
      if (_cursor_row != 0) {
        _cursor_row -= 1;
        _cursor_col = static_cast<int>(_buffer[_cursor_row].size())-1;
        return;
      }
      else {
        return;
      }
    }
    _cursor_col--;
    break;
  }
  case Command::MOVE_CURSOR_UP: {
    if (_cursor_row == 0) {
      return;
    }
    _cursor_row--;
    if (_cursor_col >= (int)_buffer[_cursor_row].size()) {
      _cursor_col = (int)_buffer[_cursor_row].size()-1;
    }
    break;
  }
  case Command::MOVE_CURSOR_FORWARD: {
    if (_cursor_col == _buffer[_cursor_row].size()-1) {
      if (_cursor_row != _buffer.size()-1) {
        _cursor_col = -1;
        _cursor_row += 1;
        return;
      }
      else {
        return;
      }
    }
    _cursor_col++;
    break;
  }
  case Command::MOVE_CURSOR_DOWN: {
    if (_cursor_row == _buffer.size()-1) {
      return;
    }
    _cursor_row++;
    if (_cursor_col >= (int)_buffer[_cursor_row].size()) {
      _cursor_col = (int)_buffer[_cursor_row].size()-1;
    }
    break;
  }
  case Command::MOVE_CURSOR_TO_HOME: {
    _cursor_col = -1;
    break;
  }
  case Command::MOVE_CURSOR_TO_END: {
    _cursor_col = (int)_buffer[_cursor_row].size()-1;
    break;
  }
  case Command::MOVE_CURSOR_TO_BUFFER_START: {
    _cursor_row = 0;
    _cursor_col = -1;
    break;
  }
  case Command::MOVE_CURSOR_TO_BUFFER_END: {
    _cursor_row = (int)_buffer.size()-1;
    _cursor_col = 0;
    break;
  }
  default: {
    break;
  }
  }
}

Result<bool, std::string> VectorBuffer::move_selection_left()
{
  if (!_has_selection) {
    _has_selection = true;
    _selection.first = {_cursor_row, _cursor_col};
  }
  VectorBuffer::execute_command(Command::MOVE_CURSOR_BACK);
  _selection.second = {_cursor_row, _cursor_col};
  if (_selection.first == _selection.second) {
    _has_selection = false;
  }
  return Ok(true);
}

Result<bool, std::string> VectorBuffer::move_selection_right()
{
  if (!_has_selection) {
    _has_selection = true;
    _selection.first = {_cursor_row, _cursor_col};
  }
  VectorBuffer::execute_command(Command::MOVE_CURSOR_FORWARD);
  _selection.second = {_cursor_row, _cursor_col};
  if (_selection.first == _selection.second) {
    _has_selection = false;
  }
  return Ok(true);
}

Result<bool, std::string> VectorBuffer::move_selection_up()
{
  if (!_has_selection) {
    _has_selection = true;
    _selection.first = {_cursor_row, _cursor_col};
  }
  VectorBuffer::execute_command(Command::MOVE_CURSOR_UP);
  _selection.second = {_cursor_row, _cursor_col};
  if (_selection.first == _selection.second) {
    _has_selection = false;
  }
  return Ok(true);
}

Result<bool, std::string> VectorBuffer::move_selection_down()
{
  if (!_has_selection) {
    _has_selection = true;
    _selection.first = {_cursor_row, _cursor_col};
  }
  VectorBuffer::execute_command(Command::MOVE_CURSOR_DOWN);
  _selection.second = {_cursor_row, _cursor_col};
  if (_selection.first == _selection.second) {
    _has_selection = false;
  }
  return Ok(true);
}

void VectorBuffer::clear_selection()
{
  _has_selection = false;
}

void VectorBuffer::move_cursor_to_word_ending()
{
  if (_cursor_col == -1) {
//    TODO
  }
}
