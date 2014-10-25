#ifndef GUI_H
#define GUI_H

#include "Utils/glodef.h"
#include <libtcod.hpp>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include "Widget/list.h"

namespace amarlon { namespace gui {

class Panel;
class List;
typedef std::shared_ptr<Panel> PanelPtr;
typedef std::shared_ptr<List> ListPtr;

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
  ~Gui() {}

  void render();
  void renderRightPanel();
  void renderMessageLog();
  void renderViewPanel(const std::vector<ColoredString>& items);

  void message(std::string msg, TCODColor color = TCODColor::white);

private:
  TCODColor _frameColor;

  PanelPtr _rightPanel;

  PanelPtr _logPanel;
  ListPtr _log;

  PanelPtr _viewPanel;
  ListPtr _viewList;

};

}}
#endif // GUI_H
