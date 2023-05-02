//
// Created by eessh on 02-05-2023.
//

#ifndef CP_BOII_BUFFER_WITH_UI_HPP
#define CP_BOII_BUFFER_WITH_UI_HPP

#include <string>
#include <vector>
#include "../result.hpp"

typedef enum class BufferCaretCommand {
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_TO_LINE_STARTING,
  MOVE_TO_LINE_ENDING,
  MOVE_TO_BUFFER_STARTING,
  MOVE_TO_BUFFER_ENDING,
} BufferCaretCommand;

typedef enum class BufferEditorCommand {
  BACKSPACE,
  ENTER,
  INSERT_CHAR,
  INSERT_STRING
} BufferEditorCommand;

class BufferWithUI {
public:
  BufferWithUI();
  explicit BufferWithUI(const std::string& text);
  explicit BufferWithUI(const std::vector<std::string>& text);

//  Getters
  [[nodiscard]] Result<std::pair<int, int>, std::string> caret_position() const;
  [[nodiscard]] Result<bool, std::string> has_selection() const;
  [[nodiscard]] Result<std::pair<std::pair<int, int>, std::pair<int, int>>, std::string> selection() const;
  [[nodiscard]] Result<std::string, std::string> selection_text() const;

//  Setters
  [[nodiscard]] Result<bool, std::string> set_caret_position(const std::pair<int, int>& position);
  [[nodiscard]] Result<bool, std::string> set_selection(const std::pair<int, int>& start, const std::pair<int, int>& end);

//  Commands
  void execute_caret_command(const BufferCaretCommand& command);
  [[nodiscard]] Result<bool, std::string> editor_backspace();
  [[nodiscard]] Result<bool, std::string> editor_enter();
  [[nodiscard]] Result<bool, std::string> editor_insert_char(const char& c);
  [[nodiscard]] Result<bool, std::string> editor_insert_string(const std::string& text);

private:
  std::vector<std::string> _buffer;
  std::pair<int, int> _caret_position;
  bool _has_selection;
  std::pair<std::pair<int, int>, std::pair<int, int>> _selection;
};

#endif //CP_BOII_BUFFER_WITH_UI_HPP
