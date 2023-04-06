#ifndef CP_BOII__CURSOR_WIDGET
#define CP_BOII__CURSOR_WIDGET

#pragma once

#include "base_widget.hpp"

class CursorWidget : public BaseWidget
{
public:
  CursorWidget();
  ~CursorWidget();

  void render() const;
};

#endif