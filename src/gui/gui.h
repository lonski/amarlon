#ifndef GUI_H
#define GUI_H

#include <memory>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <libtcod.hpp>
#include <utils/colored_string.h>

namespace amarlon { namespace gui {

class AList;
class Widget;
class Panel;
class Bar;
class Label;

typedef std::shared_ptr<AList>  AListPtr;
typedef std::shared_ptr<Panel>  PanelPtr;
typedef std::shared_ptr<Bar>    BarPtr;
typedef std::shared_ptr<Label>  LabelPtr;
typedef std::shared_ptr<Widget> WidgetPtr;

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

  void setHpBar(float value, float maxValue);
  void message(std::string msg, TCODColor color = TCODColor::white);
  void setViewList(const std::vector<ColoredString>& items);
  void setPlayerName(std::string name);
  void setStatusMessage(const std::string& status);
  void clearStatusMessage();

private:
  TCODColor _frameColor;

  AListPtr _log;
  AListPtr _viewList;
  BarPtr _hpBar;
  LabelPtr _playerName;

  std::vector<WidgetPtr> _widgets;

  void setupRightPanel();
  void setupLogPanel();
  void setupViewPanel();
};

}}
#endif // GUI_H
