#ifndef CP_BOII__TEXT_BUFFER_VECTOR_BUFFER
#define CP_BOII__TEXT_BUFFER_VECTOR_BUFFER

#pragma once

#include <string>
#include <vector>
#include "../commands.hpp"

class VectorBuffer {
  public:
  VectorBuffer();
  VectorBuffer(const std::string& str);
  VectorBuffer(const std::vector<std::string>& buffer);

  ~VectorBuffer();

  // Getters
  const std::pair<int, int> get_cursor_coords() const;
  const std::string& get_line(const unsigned int& line_number) const;
  const std::vector<std::string>& get_buffer() const;

  // Buffer Mutators
  void insert_char(const char& character);
  void insert_string(const std::string& str);

  // Command Processors
  void execute_command(const Command& command, const std::string& insert_str = "");

  private:
  int _cursor_row;
  int _cursor_col;
  std::vector<std::string> _buffer;
};

#endif