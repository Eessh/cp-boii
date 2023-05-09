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
  SDL_SetRenderDrawColor(
    SingletonRenderer::get_instance()->renderer(), 0, 0, 0, 255);
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
  if(SDL_SetRenderDrawColor(SingletonRenderer::get_instance()->renderer(),
                            color.r,
                            color.g,
                            color.b,
                            color.a) < 0)
  {
    return Error<std::string>("Unable to set render draw color!");
  }
  if(SDL_RenderFillRect(SingletonRenderer::get_instance()->renderer(),
                        &destination_rect) < 0)
  {
    return Error<std::string>("Unable to render filled rect!");
  }
  SDL_SetRenderDrawColor(
    SingletonRenderer::get_instance()->renderer(), 0, 0, 0, 255);
  return Ok(true);
}

Result<bool, std::string> DirectRender::render_filled_circle(
  const int& x, const int& y, const int& radius, const SDL_Color& color)
{
  std::vector<SDL_Point> circle_points;

  for(int w = 0; w < radius * 2; w++)
  {
    for(int h = 0; h < radius * 2; h++)
    {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if((dx * dx + dy * dy) <= (radius * radius))
      {
        circle_points.push_back({x + dx, y + dy});
      }
    }
  }

  SDL_SetRenderDrawColor(SingletonRenderer::get_instance()->renderer(),
                         color.r,
                         color.g,
                         color.b,
                         color.a);
  SDL_RenderDrawPoints(SingletonRenderer::get_instance()->renderer(),
                       circle_points.data(),
                       static_cast<int>(circle_points.size()));
  SDL_SetRenderDrawColor(
    SingletonRenderer::get_instance()->renderer(), 0, 0, 0, 255);

  return Ok(true);
}

Result<bool, std::string> DirectRender::render_filled_semicircle(
  const int& x, const int& y, const int& radius, const SDL_Color& color)
{
  std::vector<SDL_Point> circle_points;

  for(int w = 0; w < radius * 2; w++)
  {
    for(int h = radius; h >= 0; h--)
    {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if((dx * dx + dy * dy) <= (radius * radius))
      {
        circle_points.push_back({x + dx, y + dy});
      }
    }
  }

  SDL_SetRenderDrawColor(SingletonRenderer::get_instance()->renderer(),
                         color.r,
                         color.g,
                         color.b,
                         color.a);
  SDL_RenderDrawPoints(SingletonRenderer::get_instance()->renderer(),
                       circle_points.data(),
                       static_cast<int>(circle_points.size()));
  SDL_SetRenderDrawColor(
    SingletonRenderer::get_instance()->renderer(), 0, 0, 0, 255);

  return Ok(true);
}

Result<bool, std::string> DirectRender::render_filled_inverted_semicircle(
  const int& x, const int& y, const int& radius, const SDL_Color& color)
{
  std::vector<SDL_Point> circle_points;

  for(int w = 1; w < radius * 2; w++)
  {
    for(int h = 0; h <= radius; h++)
    {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if((dx * dx + dy * dy) <= (radius * radius))
      {
        circle_points.push_back({x + dx, y + dy});
      }
    }
  }

  SDL_SetRenderDrawColor(SingletonRenderer::get_instance()->renderer(),
                         color.r,
                         color.g,
                         color.b,
                         color.a);
  SDL_RenderDrawPoints(SingletonRenderer::get_instance()->renderer(),
                       circle_points.data(),
                       static_cast<int>(circle_points.size()));
  SDL_SetRenderDrawColor(
    SingletonRenderer::get_instance()->renderer(), 0, 0, 0, 255);

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
                               const int& line_number,
                               const int& max_line_number,
                               const bool& is_active,
                               const SDL_Color& foreground,
                               const SDL_Color& background,
                               const SDL_Color& active_background,
                               const SDL_Color& line_number_foreground,
                               const SDL_Color& line_number_background,
                               const SDL_Color& line_number_active_foreground,
                               const SDL_Color& line_number_active_background)
{
  //  Drawing line number
  std::string line_number_str = std::to_string(line_number + 1),
              max_line_number_str = std::to_string(max_line_number);
  int char_difference =
    (int)(max_line_number_str.length() - line_number_str.length());
  while(char_difference--)
  {
    line_number_str.insert(line_number_str.begin(), ' ');
  }
  line_number_str.insert(line_number_str.begin(), ' ');
  line_number_str.push_back(' ');
  std::pair<unsigned int, unsigned int> line_number_str_dimensions =
    FontManager::get_instance()->get_text_dimensions(line_number_str);
  SDL_Texture* line_number_texture =
    TextureManager::get_instance()->get_colored_string_texture(
      line_number_str,
      is_active ? line_number_active_foreground : line_number_foreground);
  if(!line_number_texture)
  {
    return Error<std::string>("Unable to create texture for line number!");
  }
  SDL_Rect line_number_destination_rect{
    .x = x,
    .y = y,
    .w = static_cast<int>(line_number_str_dimensions.first),
    .h = static_cast<int>(line_number_str_dimensions.second)};
  DirectRender::render_filled_rectangle(
    x,
    y,
    static_cast<int>(line_number_str_dimensions.first),
    static_cast<int>(line_number_str_dimensions.second),
    is_active ? line_number_active_background : line_number_background);
  SDL_RenderCopy(SingletonRenderer::get_instance()->renderer(),
                 line_number_texture,
                 nullptr,
                 &line_number_destination_rect);
  SDL_DestroyTexture(line_number_texture);

  //  Drawing line background
  if(line.length() < 1)
  {
    int character_height =
      static_cast<int>(TextureManager::get_instance()
                         ->get_alphabet_char_texture_dimensions('a')
                         .second);
    DirectRender::render_filled_rectangle(x + line_number_destination_rect.w,
                                          y,
                                          view_width,
                                          character_height,
                                          is_active ? active_background
                                                    : background);
    return Ok(true);
  }

  //  Drawing line text
  SDL_Texture* line_texture =
    TextureManager::get_instance()->get_colored_string_texture(line,
                                                               foreground);
  if(!line_texture)
  {
    return Error<std::string>("Unable to create texture for given line!");
  }

  std::pair<unsigned int, unsigned int> line_texture_dimensions =
    FontManager::get_instance()->get_text_dimensions(line);
  SDL_Rect destination_rect{.x = x + line_number_destination_rect.w,
                            .y = y,
                            .w = (int)line_texture_dimensions.first,
                            .h = (int)line_texture_dimensions.second};
  DirectRender::render_filled_rectangle(x + line_number_destination_rect.w,
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

Result<uint32_t, std::string> DirectRender::rgba_to_hex(const SDL_Color& color)
{
  return Ok<uint32_t>(((color.r & 0xff) << 24) + ((color.g & 0xff) << 16) +
                      ((color.b & 0xff) << 8) + (color.a & 0xff));
}
