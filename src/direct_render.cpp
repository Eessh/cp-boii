//
// Created by eessh on 04-05-2023.
//

#include "../include/direct_render.hpp"
#include "../log-boii/log_boii.h"

Result<bool, std::string>
DirectRender::render_rectangle(const int& x,
                               const int& y,
                               const int& width,
                               const int& height,
                               const SDL_Color& outline_color)
{
  SDL_Rect destination_rect{.x = x, .y = y, .w = width, .h = height};
  SDL_SetRenderDrawColor(SingletonRenderer::get_instance()->renderer(),
                         outline_color.r,
                         outline_color.g,
                         outline_color.b,
                         outline_color.a);
  SDL_RenderDrawRect(SingletonRenderer::get_instance()->renderer(),
                     &destination_rect);
  return Ok(true);
}

Result<bool, std::string>
DirectRender::render_filled_rectangle(const int& x,
                                      const int& y,
                                      const int& width,
                                      const int& height,
                                      const SDL_Color& color)
{
  SDL_Rect destination_rect{.x = x, .y = y, .w = width, .h = height};
  SDL_SetRenderDrawColor(SingletonRenderer::get_instance()->renderer(),
                         color.r,
                         color.g,
                         color.b,
                         color.a);
  SDL_RenderFillRect(SingletonRenderer::get_instance()->renderer(),
                     &destination_rect);
  return Ok(true);
}

Result<bool, std::string> DirectRender::render_character(const int& x,
                                                         const int& y,
                                                         const char& character,
                                                         const SDL_Color& color)
{
  SDL_Texture* character_texture =
    TextureManager::get_instance()->get_colored_alphabet_char_texture(character,
                                                                      color);
  if(!character_texture)
  {
    return Error<std::string>("Unable to create texture for given character!");
  }

  std::pair<const unsigned int&, const unsigned int&>
    character_texture_dimensions =
      TextureManager::get_instance()->get_alphabet_char_texture_dimensions(
        character);
  SDL_Rect destination_rect{.x = x,
                            .y = y,
                            .w = (int)character_texture_dimensions.first,
                            .h = (int)character_texture_dimensions.second};
  SDL_RenderCopy(SingletonRenderer::get_instance()->renderer(),
                 character_texture,
                 nullptr,
                 &destination_rect);
  SDL_DestroyTexture(character_texture);
  return Ok(true);
}

Result<bool, std::string> DirectRender::render_string(const int& x,
                                                      const int& y,
                                                      const std::string& text,
                                                      const SDL_Color& color)
{
  SDL_Texture* text_texture =
    TextureManager::get_instance()->get_colored_string_texture(text, color);
  if(!text_texture)
  {
    return Error<std::string>("Unable to create texture for given string!");
  }

  std::pair<unsigned int, unsigned int> text_texture_dimensions =
    FontManager::get_instance()->get_text_dimensions(text);
  SDL_Rect destination_rect{.x = x,
                            .y = y,
                            .w = (int)text_texture_dimensions.first,
                            .h = (int)text_texture_dimensions.second};
  SDL_RenderCopy(SingletonRenderer::get_instance()->renderer(),
                 text_texture,
                 nullptr,
                 &destination_rect);
  SDL_DestroyTexture(text_texture);
  return Ok(true);
}

Result<bool, std::string>
DirectRender::render_line_view(const int& x,
                               const int& y,
                               const int& view_width,
                               const std::string& line,
                               const bool& is_active,
                               const SDL_Color& foreground,
                               const SDL_Color& background,
                               const SDL_Color& active_background)
{
  if(line.length() < 1)
  {
    int character_height =
      static_cast<int>(TextureManager::get_instance()
                         ->get_alphabet_char_texture_dimensions('a')
                         .second);
    DirectRender::render_filled_rectangle(x,
                                          y,
                                          view_width,
                                          character_height,
                                          is_active ? active_background
                                                    : background);
    return Ok(true);
  }

  SDL_Texture* line_texture =
    TextureManager::get_instance()->get_colored_string_texture(line,
                                                               foreground);
  if(!line_texture)
  {
    return Error<std::string>("Unable to create texture for given line!");
  }

  std::pair<unsigned int, unsigned int> line_texture_dimensions =
    FontManager::get_instance()->get_text_dimensions(line);
  SDL_Rect destination_rect{.x = x,
                            .y = y,
                            .w = (int)line_texture_dimensions.first,
                            .h = (int)line_texture_dimensions.second};
  DirectRender::render_filled_rectangle(x,
                                        y,
                                        view_width,
                                        (int)line_texture_dimensions.second,
                                        is_active ? active_background
                                                  : background);
  //  int painter_x = x, painter_y = y;
  //  int character_width = (int)TextureManager::get_instance()->get_alphabet_char_texture_dimensions('a').first;
  //  for (const char& c: line) {
  //    DirectRender::render_character(painter_x, painter_y, c, foreground);
  //    painter_x += character_width;
  //  }
  if(SDL_RenderCopy(SingletonRenderer::get_instance()->renderer(),
                    line_texture,
                    nullptr,
                    &destination_rect) < 0)
  {
#ifdef DEBUG
    log_error("Unable to copy the line texture!");
#endif
  }
  SDL_DestroyTexture(line_texture);
  return Ok(true);
}