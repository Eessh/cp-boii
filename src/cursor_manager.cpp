//
// Created by eessh on 06-05-2023.
//

#include "../include/cursor_manager.hpp"
#include "../log-boii/log_boii.h"

CursorManager* CursorManager::_instance = nullptr;

CursorManager::CursorManager()
  : _arrow(nullptr)
  , _crosshair(nullptr)
  , _double_arrow_left_to_right(nullptr)
  , _double_arrow_top_left_to_bottom_right(nullptr)
  , _double_arrow_top_right_to_bottom_left(nullptr)
  , _double_arrow_top_to_down(nullptr)
  , _hand(nullptr)
  , _ibeam(nullptr)
  , _loading(nullptr)
  , _prohibited(nullptr)
  , _small_loading(nullptr)
  , _drag(nullptr)
{}

CursorManager::~CursorManager() noexcept
{
  SDL_FreeCursor(_arrow);
  SDL_FreeCursor(_crosshair);
  SDL_FreeCursor(_double_arrow_top_to_down);
  SDL_FreeCursor(_double_arrow_top_right_to_bottom_left);
  SDL_FreeCursor(_double_arrow_top_left_to_bottom_right);
  SDL_FreeCursor(_double_arrow_left_to_right);
  SDL_FreeCursor(_small_loading);
  SDL_FreeCursor(_loading);
  SDL_FreeCursor(_prohibited);
  SDL_FreeCursor(_ibeam);
  SDL_FreeCursor(_hand);
  SDL_FreeCursor(_drag);
}

void CursorManager::create_instance()
{
  if(_instance != nullptr)
  {
    log_warn("Cursor Manager instance already exists, use "
             "CursorManager::get_instance()");
    return;
  }
  log_info("Creating Cursor Manager...");
  _instance = new CursorManager();
}

void CursorManager::delete_instance()
{
  log_info("Deleting Cursor Manager instance...");
  delete _instance;
}

CursorManager* CursorManager::get_instance()
{
  return _instance;
}

void CursorManager::initialize()
{
  log_info("Loading system cursors...");
  _arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
  _ibeam = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
  _loading = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
  _small_loading = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW);
  _crosshair = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
  _double_arrow_top_left_to_bottom_right =
    SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
  _double_arrow_top_right_to_bottom_left =
    SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
  _double_arrow_left_to_right =
    SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
  _double_arrow_top_to_down = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
  _drag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
  _prohibited = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
  _hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}

void CursorManager::set_arrow() const
{
  SDL_SetCursor(_arrow);
}

void CursorManager::set_crosshair() const
{
  SDL_SetCursor(_crosshair);
}

void CursorManager::set_double_arrow_left_to_right() const
{
  SDL_SetCursor(_double_arrow_left_to_right);
}

void CursorManager::set_double_arrow_top_left_to_bottom_right() const
{
  SDL_SetCursor(_double_arrow_top_left_to_bottom_right);
}

void CursorManager::set_double_arrow_top_right_to_bottom_left() const
{
  SDL_SetCursor(_double_arrow_top_right_to_bottom_left);
}

void CursorManager::set_double_arrow_top_to_down() const
{
  SDL_SetCursor(_double_arrow_top_to_down);
}

void CursorManager::set_hand() const
{
  SDL_SetCursor(_hand);
}

void CursorManager::set_ibeam() const
{
  SDL_SetCursor(_ibeam);
}

void CursorManager::set_loading() const
{
  SDL_SetCursor(_loading);
}

void CursorManager::set_prohibited() const
{
  SDL_SetCursor(_prohibited);
}

void CursorManager::set_small_loading() const
{
  SDL_SetCursor(_small_loading);
}