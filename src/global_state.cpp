#include "../include/global_state.hpp"

GlobalState* GlobalState::_instance = nullptr;

GlobalState::GlobalState()
  : _last_time(SDL_GetTicks()), _current_time(_last_time)
{}

GlobalState::~GlobalState() {}

void GlobalState::create_instance()
{
  if(_instance)
  {
    return;
  }
  _instance = new GlobalState();
}

GlobalState* GlobalState::get_instance()
{
  return _instance;
}

void GlobalState::delete_instance()
{
  delete _instance;
}

const Uint32& GlobalState::last_time() const
{
  return _last_time;
}

const Uint32& GlobalState::current_time() const
{
  return _current_time;
}

const float& GlobalState::delta_time() const
{
  return _delta_time;
}

void GlobalState::update_time()
{
  _current_time = SDL_GetTicks();
  _delta_time = (float)(_current_time - _last_time) / 1000.0f;
  _last_time = _current_time;
}