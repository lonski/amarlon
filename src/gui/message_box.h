#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <string>
#include <libtcod.hpp>
#include <gui/window/text_window.h>
#include <Engine.h>

namespace amarlon { namespace gui {

static inline void msgError(const std::string& text)
{
  Engine::instance().windowManager()
                    .getWindow<TextWindow>()
                    .setWindowFrameColor(TCODColor::red)
                    .setWindowText(text)
                    .show();
}

static inline void msgInfo(const std::string& text)
{
  Engine::instance().windowManager()
                    .getWindow<TextWindow>()
                    .setWindowFrameColor(TCODColor::darkerOrange)
                    .setWindowText(text)
                    .show();
}

}}

#endif // MESSAGEBOX_H
