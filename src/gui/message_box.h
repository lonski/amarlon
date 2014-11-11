#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <string>
#include <libtcod.hpp>
#include <gui/window/text_window/resizeable_text_window.h>
#include <engine.h>

namespace amarlon { namespace gui {

static inline void msgError(const std::string& text)
{
  Engine::instance().windowManager()
                    .getWindow<ResizeableTextWindow>()
                    .setWindowFrameColor(TCODColor::red)
                    .setWindowText(text)
                    .show();
}

static inline void msgInfo(const std::string& text)
{
  Engine::instance().windowManager()
                    .getWindow<ResizeableTextWindow>()
                    .setWindowFrameColor(TCODColor::darkerOrange)
                    .setWindowText(text)
                    .show();
}

}}

#endif // MESSAGEBOX_H
