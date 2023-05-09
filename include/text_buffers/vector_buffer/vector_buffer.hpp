#ifndef CP_BOII__TEXT_BUFFER_VECTOR_BUFFER
#define CP_BOII__TEXT_BUFFER_VECTOR_BUFFER

#pragma once

#include <string>
#include <vector>
#include "../commands.hpp"
#include "../../result.hpp"

class VectorBuffer {
  public:
  VectorBuffer();
  explicit VectorBuffer(const std::string& str);
  explicit VectorBuffer(const std::vector<std::string>& buffer);

  ~VectorBuffer() = default;

  // Getters
  [[nodiscard]] Result<std::pair<int, int>, std::string> get_cursor_coords() const;
  [[nodiscard]] Result<const std::string&, std::string> get_line(const unsigned int& line_number) const;
  [[nodiscard]] bool has_selection() const;
  [[nodiscard]] Result<const std::pair<std::pair<int, int>, std::pair<int, int>>&, std::string> get_selection() const;
  [[nodiscard]] std::string get_line_unsafe(const unsigned int& line_number) const;
  [[nodiscard]] Result<const std::vector<std::string>&, std::string> get_buffer() const;
  [[nodiscard]] int size() const;

//  Setters
  Result<bool, std::string> set_cursor_coords(const int& row, const int& column);
  Result<bool, std::string> set_selection(const std::pair<std::pair<int, int>, std::pair<int, int>>& selection);

  // Buffer Mutators
  [[nodiscard]] Result<bool, std::string> insert_char(const char& character);
  [[nodiscard]] Result<bool, std::string> insert_string(const std::string& str);

  // Command Processors
  void execute_command(const Command& command, const std::string& insert_str = "");
  Result<bool, std::string> move_selection_left();
  Result<bool, std::string> move_selection_right();
  Result<bool, std::string> move_selection_up();
  Result<bool, std::string> move_selection_down();
  void clear_selection();
  void move_cursor_to_word_ending();

  private:
  int _cursor_row;
  int _cursor_col;
  bool _has_selection;
  std::pair<std::pair<int, int>, std::pair<int, int>> _selection;
  std::vector<std::string> _buffer;
};

#endif