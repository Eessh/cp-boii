#ifndef CP_BOII__GLOBAL_STATE
#define CP_BOII__GLOBAL_STATE

#pragma once

#include "../SDL2/include/SDL.h"

class GlobalState
{
public:
  // Deleting copy constructor
  GlobalState(const GlobalState& global_state) = delete;
  // Deleting copy operator
  GlobalState operator=(const GlobalState& global_state) = delete;

  ~GlobalState();

  static void create_instance();
  static GlobalState* get_instance();
  static void delete_instance();

  [[nodiscard]] const Uint32& last_time() const;
  [[nodiscard]] const Uint32& current_time() const;
  [[nodiscard]] const float& delta_time() const;

  void update_time();

private:
  Uint32 _last_time;
  Uint32 _current_time;
  float _delta_time;

  // Constructors
  GlobalState();

  static GlobalState* _instance;
};

#endif