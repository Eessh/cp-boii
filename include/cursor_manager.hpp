//
// Created by eessh on 06-05-2023.
//

#ifndef CP_BOII_CURSOR_MANAGER_HPP
#define CP_BOII_CURSOR_MANAGER_HPP

#pragma once

#include "../SDL2/include/SDL.h"

class CursorManager {
public:
//  Deleting copy constructor
  CursorManager(const CursorManager& cursor_manager) = delete;
//  Deleting move constructor
  CursorManager(CursorManager&& cursor_manager) = delete;
//  Deleting copy operator
  CursorManager operator = (const CursorManager& cursor_manager) = delete;

  ~CursorManager();

  static void create_instance();
  static CursorManager* get_instance();
  static void delete_instance();

  void initialize();

//  Setters
  void set_arrow() const;
  void set_ibeam() const;
  void set_loading() const;
  void set_small_loading() const;
  void set_crosshair() const;
  void set_double_arrow_left_to_right() const;
  void set_double_arrow_top_to_down() const;
  void set_double_arrow_top_left_to_bottom_right() const;
  void set_double_arrow_top_right_to_bottom_left() const;
  void set_prohibited() const;
  void set_hand() const;

private:
  SDL_Cursor* _arrow;
  SDL_Cursor* _ibeam;
  SDL_Cursor* _loading;
  SDL_Cursor* _small_loading;
  SDL_Cursor* _crosshair;
  SDL_Cursor* _double_arrow_left_to_right;
  SDL_Cursor* _double_arrow_top_to_down;
  SDL_Cursor* _double_arrow_top_left_to_bottom_right;
  SDL_Cursor* _double_arrow_top_right_to_bottom_left;
  SDL_Cursor* _prohibited;
  SDL_Cursor* _hand;
  SDL_Cursor* _drag;

//  Constructors
  CursorManager();

  static CursorManager* _instance;
};

#endif //CP_BOII_CURSOR_MANAGER_HPP
