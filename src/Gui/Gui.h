#ifndef GUI_H
#define GUI_H

#include "Utils/glodef.h"
#include <libtcod.hpp>
#include <string>
#include <list>
#include <utility>

class Gui
{
public:
  const size_t LogSize = 17;

  const int bottomConWidth = 20;
  const int bottomConHeight = gloScreenHeight;

  const int rightConWidth = gloScreenWidth - 20;
  const int rightConHeight = 20;

  Gui();
  ~Gui();

  void render();
  void renderRightPanel();
  void renderBottomPanel();

  void message(std::string msg, TCODColor color = TCODColor::white);

private:
  struct LogEntry
  {
    std::string msg;
    TCODColor color;

    LogEntry(const std::string& m, TCODColor c)
      : msg(m)
      , color(c)
    {}
  };

  std::list< LogEntry > _msgLog;
  TCODColor _frameColor;

  TCODConsole* rCon;
  TCODConsole* bCon;

  void renderMessageLog();

};

#endif // GUI_H
