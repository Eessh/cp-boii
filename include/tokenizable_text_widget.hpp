#ifndef CP_BOII__TOKENIZABLE_TEXT_WIDGET
#define CP_BOII__TOKENIZABLE_TEXT_WIDGET

#pragma once

#include <string>
#include "base_widget.hpp"

class TokenizableTextWidget : public BaseWidget
{
public:
  explicit TokenizableTextWidget(const std::string& text);
  ~TokenizableTextWidget() = default;

  // Getters
  [[nodiscard]] const std::string& text() const;

  // Setters
  std::string& text();

  // Processors
  void process_sdl_event(const SDL_Event& event);

  void render() const;

private:
  std::string _text;
};

#endif