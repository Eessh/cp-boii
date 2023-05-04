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
  [[nodiscard]] std::string get_line_unsafe(const unsigned int& line_number) const;
  [[nodiscard]] Result<const std::vector<std::string>&, std::string> get_buffer() const;
  [[nodiscard]] int size() const;

  // Buffer Mutators
  [[nodiscard]] Result<bool, std::string> insert_char(const char& character);
  [[nodiscard]] Result<bool, std::string> insert_string(const std::string& str);

  // Command Processors
  void execute_command(const Command& command, const std::string& insert_str = "");

  private:
  int _cursor_row;
  int _cursor_col;
  std::vector<std::string> _buffer;
};

#endif