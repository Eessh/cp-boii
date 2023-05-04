//
// Created by eessh on 03-05-2023.
//

#ifndef CP_BOII_DIRECT_RENDER_HPP
#define CP_BOII_DIRECT_RENDER_HPP

#include <string>
#include "font_manager.hpp"
#include "result.hpp"
#include "singleton_renderer.hpp"
#include "texture_manager.hpp"

namespace DirectRender
{

Result<bool, std::string> render_rectangle(const int& x,
                                           const int& y,
                                           const int& width,
                                           const int& height,
                                           const SDL_Color& outline_color);
Result<bool, std::string> render_filled_rectangle(const int& x,
                                                  const int& y,
                                                  const int& width,
                                                  const int& height,
                                                  const SDL_Color& color);
Result<bool, std::string> render_character(const int& x,
                                           const int& y,
                                           const char& character,
                                           const SDL_Color& color);
Result<bool, std::string> render_string(const int& x,
                                        const int& y,
                                        const std::string& text,
                                        const SDL_Color& color);
Result<bool, std::string> render_line_view(const int& x,
                                           const int& y,
                                           const int& view_width,
                                           const std::string& line,
                                           const bool& is_active,
                                           const SDL_Color& foreground,
                                           const SDL_Color& background,
                                           const SDL_Color& active_background);

}; // namespace DirectRender

#endif //CP_BOII_DIRECT_RENDER_HPP
