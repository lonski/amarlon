#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <string>
#include <libtcod.hpp>
#include <Gui/text_window.h>

namespace amarlon { namespace gui {

static inline void msgError(const std::string& text)
{
  TextWindow msg(text);
  msg.setFrameColor(TCODColor::red);
  msg.show(*TCODConsole::root);
}

static inline void msgInfo(const std::string& text)
{
  TextWindow msg(text);
  msg.setFrameColor(TCODColor::darkerOrange);
  msg.show(*TCODConsole::root);
}

}}

#endif // MESSAGEBOX_H
