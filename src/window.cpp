#include "../include/window.hpp"
#include "../log-boii/log_boii.h"
#ifdef _WIN64
#  include "SDL_syswm.h"
//define something for Windows (64-bit only)
#elif _WIN32
#  include "SDL_syswm.h"
#endif

Window::Window(const std::string& title,
               unsigned int width,
               unsigned int height,
               Uint32 flags)
  : _title(title)
  , _x(SDL_WINDOWPOS_CENTERED)
  , _y(SDL_WINDOWPOS_CENTERED)
  , _width(width)
  , _height(height)
  , _flags(flags)
{
  log_info("Creating window...");
  _window = SDL_CreateWindow(_title.c_str(), _x, _y, _width, _height, _flags);
  if(!_window)
  {
    log_fatal("Error while creating window: %s", SDL_GetError());
    _ok = false;
    _window = NULL;
  }
}

Window::Window(const std::string& title,
               unsigned int x,
               unsigned int y,
               unsigned int width,
               unsigned int height,
               Uint32 flags)
  : _title(title), _x(x), _y(y), _width(width), _height(height), _flags(flags)
{
  log_info("Creating window...");
  _window = SDL_CreateWindow(_title.c_str(), _x, _y, _width, _height, _flags);
  if(!_window)
  {
    log_fatal("Error while creating window: %s", SDL_GetError());
    _ok = false;
    _window = NULL;
  }
}

Window::Window(const WindowConfig& config)
  : _title(config.title)
  , _x(config.x)
  , _y(config.y)
  , _width(config.width)
  , _height(config.height)
  , _flags(config.flags)
{
  _window = SDL_CreateWindow(_title.c_str(), _x, _y, _width, _height, _flags);
  if(!_window)
  {
    log_fatal("Error while creating window: %s", SDL_GetError());
    _ok = false;
    _window = NULL;
  }
}

Window::~Window()
{
  log_info("Freeing up resources used by window...");
  SDL_DestroyWindow(_window);
}

unsigned int Window::x() const
{
  return _x;
}

unsigned int Window::y() const
{
  return _y;
}

unsigned int Window::width() const
{
  return _width;
}

unsigned int Window::height() const
{
  return _height;
}

const std::string& Window::title() const
{
  return _title;
}

unsigned int& Window::x()
{
  return _x;
}

unsigned int& Window::y()
{
  return _y;
}

unsigned int& Window::width()
{
  return _width;
}

unsigned int& Window::height()
{
  return _height;
}

std::string& Window::title()
{
  return _title;
}

void Window::set_dark_mode()
{
#ifdef _WIN64
  SDL_SysWMinfo wmi;
  SDL_VERSION(&wmi.version);
  SDL_GetWindowWMInfo(_window, &wmi);
  auto hwnd = wmi.info.win.window;

  auto uxtheme = LoadLibraryA("uxtheme.dll");
  auto dwm = LoadLibraryA("dwmapi.dll");

  if(uxtheme && dwm)
  {
    typedef HRESULT (*SetWindowThemePTR)(HWND, const wchar_t*, const wchar_t*);
    auto SetWindowTheme =
      (SetWindowThemePTR)GetProcAddress(uxtheme, "SetWindowTheme");

    typedef HRESULT (*DwmSetWindowAttributePTR)(HWND, DWORD, LPCVOID, DWORD);
    auto DwmSetWindowAttribute =
      (DwmSetWindowAttributePTR)GetProcAddress(dwm, "DwmSetWindowAttribute");

    if(SetWindowTheme && DwmSetWindowAttribute)
    {
      SetWindowTheme(hwnd, L"DarkMode_Explorer", nullptr);

      BOOL darkMode = 1;
      if(!DwmSetWindowAttribute(hwnd, 20, &darkMode, sizeof darkMode))
      {
        DwmSetWindowAttribute(hwnd, 19, &darkMode, sizeof darkMode);
      }
    }
  }
#elif _WIN32
  SDL_SysWMinfo wmi;
  SDL_VERSION(&wmi.version);
  SDL_GetWindowWMInfo(_window, &wmi);
  auto hwnd = wmi.info.win.window;

  auto uxtheme = LoadLibraryA("uxtheme.dll");
  auto dwm = LoadLibraryA("dwmapi.dll");

  if(uxtheme && dwm)
  {
    typedef HRESULT (*SetWindowThemePTR)(HWND, const wchar_t*, const wchar_t*);
    auto SetWindowTheme =
      (SetWindowThemePTR)GetProcAddress(uxtheme, "SetWindowTheme");

    typedef HRESULT (*DwmSetWindowAttributePTR)(HWND, DWORD, LPCVOID, DWORD);
    auto DwmSetWindowAttribute =
      (DwmSetWindowAttributePTR)GetProcAddress(dwm, "DwmSetWindowAttribute");

    if(SetWindowTheme && DwmSetWindowAttribute)
    {
      SetWindowTheme(hwnd, L"DarkMode_Explorer", nullptr);

      BOOL darkMode = 1;
      if(!DwmSetWindowAttribute(hwnd, 20, &darkMode, sizeof darkMode))
      {
        DwmSetWindowAttribute(hwnd, 19, &darkMode, sizeof darkMode);
      }
    }
  }
#endif

  // Paints the background of the window black
  //  PAINTSTRUCT ps;
  //  RECT rc;
  //  HDC hdc = BeginPaint(hwnd, &ps);
  //  GetClientRect(hwnd, &rc);
  //  SetBkColor(hdc, BLACK_BRUSH);
  //  ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rc, 0, 0, 0);
  //  EndPaint(hwnd, &ps);
}

void Window::set_icon(const std::string& icon_file_path)
{
  SDL_Surface* icon_surface = nullptr;
  icon_surface = SDL_LoadBMP(icon_file_path.c_str());
  if(!icon_surface)
  {
    // TODO: handle dis
    return;
  }

  SDL_SetWindowIcon(_window, icon_surface);
  SDL_FreeSurface(icon_surface);
}

bool Window::ok() const
{
  return _ok;
}
