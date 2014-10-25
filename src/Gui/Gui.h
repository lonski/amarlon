#ifndef GUI_H
#define GUI_H

#include "Utils/glodef.h"
#include <libtcod.hpp>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include "Utils/LogEntry.h"

class Gui
{
public:
  const size_t LogSize;

  const int rightConWidth;
  const int rightConHeight;

  const int bottomConWidth;
  const int bottomConHeight;

  const int logConWidth;
  const int logConHeight;

  const int viewConWidth;
  const int viewConHeight;

  Gui();
  ~Gui();

  void render();
  void renderRightPanel();
  void renderMessageLog();
  void renderViewPanel(const std::vector<LogEntry>& items);

  void message(std::string msg, TCODColor color = TCODColor::white);

private:

  std::list< LogEntry > _msgLog;
  TCODColor _frameColor;

  TCODConsole* rCon;
  TCODConsole* bCon;

  TCODConsole* logCon;
  TCODConsole* viewCon;


};

#endif // GUI_H
