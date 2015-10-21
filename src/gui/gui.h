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
class AWidget;
class APanel;
class ABar;
class ALabel;

typedef std::shared_ptr<AList>   AListPtr;
typedef std::shared_ptr<APanel>  APanelPtr;
typedef std::shared_ptr<ABar>    ABarPtr;
typedef std::shared_ptr<ALabel>  ALabelPtr;
typedef std::shared_ptr<AWidget> AWidgetPtr;

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
  void setExpBar(float value, float maxValue);
  void message(std::string msg, TCODColor color = TCODColor::white);
  void clearLog();
  void setViewList(const std::vector<ColoredString>& items);
  void setEffectsList(const std::vector<ColoredString>& items);
  void setPlayerName(std::string name);
  void setPlayerLevel(std::string level);
  void setStatusMessage(const std::string& status);
  void clearStatusMessage();

private:
  TCODColor _frameColor;

  AListPtr _log;
  AListPtr _viewList;
  ABarPtr _hpBar;
  ABarPtr _expBar;
  ALabelPtr _playerName;
  ALabelPtr _playerLevel;
  AListPtr _effects;

  std::vector<AWidgetPtr> _widgets;

  void setupRightPanel();
  void setupLogPanel();
  void setupViewPanel();
};

}}
#endif // GUI_H
