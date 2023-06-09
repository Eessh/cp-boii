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
//#include "../olive.c/olive.c"

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

Result<bool, std::string> render_filled_circle(const int& x,
                                               const int& y,
                                               const int& radius,
                                               const SDL_Color& color);

Result<bool, std::string> render_filled_semicircle(const int& x,
                                                   const int& y,
                                                   const int& radius,
                                                   const SDL_Color& color);

Result<bool, std::string> render_filled_inverted_semicircle(
  const int& x, const int& y, const int& radius, const SDL_Color& color);

Result<bool, std::string> render_character(const int& x,
                                           const int& y,
                                           const char& character,
                                           const SDL_Color& color);

Result<bool, std::string> render_string(const int& x,
                                        const int& y,
                                        const std::string& text,
                                        const SDL_Color& color);

Result<bool, std::string>
render_line_view(const int& x,
                 const int& y,
                 const int& view_width,
                 const std::string& line,
                 const int& line_number,
                 const int& max_line_number,
                 const bool& is_active,
                 const SDL_Color& foreground,
                 const SDL_Color& background,
                 const SDL_Color& active_background,
                 const SDL_Color& line_number_foreground,
                 const SDL_Color& line_number_background,
                 const SDL_Color& line_number_active_foreground,
                 const SDL_Color& line_number_active_background);

Result<uint32_t, std::string> rgba_to_hex(const SDL_Color& color);

}; // namespace DirectRender

#endif //CP_BOII_DIRECT_RENDER_HPP
