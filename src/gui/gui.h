#ifndef GUI_H
#define GUI_H

#include <libtcod.hpp>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include "widget/list.h"

namespace amarlon { namespace gui {

class Panel;
class List;
class Bar;
class Label;

typedef std::shared_ptr<Panel> PanelPtr;
typedef std::shared_ptr<List> ListPtr;
typedef std::shared_ptr<Bar> BarPtr;
typedef std::shared_ptr<Label> LabelPtr;

class Gui
{
public:
  const int rightConWidth;
  const int rightConHeight;

  const int bottomConWidth;
  const int bottomConHeight;

  const int logConWidth;
  const int logConHeight;

  const int viewConWidth;
  const int viewConHeight;

  const size_t LogSize;

  Gui();
  ~Gui() {}

  void render();

  void message(std::string msg, TCODColor color = TCODColor::white);
  void setStatusMessage(const std::string& status);
  void clearStatusMessage();
  void setViewList(const std::vector<ColoredString>& items);
  void setHpBar(float value, float maxValue);
  void setPlayerName(std::string name);

private:
  TCODColor _frameColor;

  ListPtr _log;
  ListPtr _viewList;
  BarPtr _hpBar;
  LabelPtr _playerName;

  std::vector<WidgetPtr> _widgets;

  void setupRightPanel();
  void setupLogPanel();
  void setupViewPanel();
};

}}
#endif // GUI_H
