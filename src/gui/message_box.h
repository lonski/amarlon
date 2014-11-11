#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <string>
#include <libtcod.hpp>
#include <gui/window/text_window/resizeable_text_window.h>
#include <engine.h>

namespace amarlon { namespace gui {

enum class MsgType
{
  Error,
  Warning,
  Info
};

static inline void msgBox(const std::string& text, MsgType type)
{
  TCODColor color;
  switch (type)
  {
    case MsgType::Error: color = TCODColor::red; break;
    case MsgType::Warning: color = TCODColor::yellow; break;
    case MsgType::Info: color = TCODColor::darkerOrange; break;
  }

  Engine::instance().windowManager()
                    .getWindow<ResizeableTextWindow>()
                    .setWindowFrameColor(color)
                    .setWindowText(text)
                    .setCenterGameScreen()
                    .show();
}

}}

#endif // MESSAGEBOX_H
