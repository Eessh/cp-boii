#ifndef CP_BOII__STRING_WIDGET
#define CP_BOII__STRING_WIDGET

#pragma once

#include <string>
#include "base_widget.hpp"

class StringWidget : public BaseWidget
{
public:
  explicit StringWidget(const std::string& text);

  ~StringWidget();

  // Getters
  [[nodiscard]] const std::string& text() const;

  // Setters
  std::string& text();

  void process_sdl_event(const SDL_Event& event);

  void render() const;

private:
  std::string _text;

  // SDL_Texture* _texture;

  // private methods, for handling internal state change
  // void update_texture();
};

#endif