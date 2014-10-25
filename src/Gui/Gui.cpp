#include "Gui.h"
#include <algorithm>
#include <iostream>
#include "Widget/panel.h"
#include "Widget/list.h"
#include "Widget/bar.h"
#include "Widget/label.h"

namespace amarlon { namespace gui {

Gui::Gui()
  : LogSize(17)
  , rightConWidth(20)
  , rightConHeight(gloScreenHeight)
  , bottomConWidth(gloScreenWidth - 20)
  , bottomConHeight(20)
  , logConWidth((gloScreenWidth - 20) / 2)
  , logConHeight(20)
  , viewConWidth((gloScreenWidth - 20) / 2)
  , viewConHeight(20)
  , _frameColor(TCODColor::darkerOrange)

{
  setupRightPanel();
  setupLogPanel();
  setupViewPanel();
}

void Gui::setupRightPanel()
{
  PanelPtr rightPanel( new Panel(rightConWidth, rightConHeight) );
  rightPanel->setPosition( gloScreenWidth - rightConWidth, 0 );

  _playerName.reset( new Label );
  _playerName->setPosition(2,2);
  rightPanel->addWidget(_playerName);

  _hpBar.reset( new Bar );
  _hpBar->setPosition(2,4);
  _hpBar->setName("HP");
  _hpBar->setWidth( rightPanel->getWidth() - 4 );
  rightPanel->addWidget(_hpBar);

  _widgets.push_back( rightPanel );
}

void Gui::setupLogPanel()
{
  _log.reset(new List);
  _log->setPosition(2,1);
  _log->setMaxSize(LogSize);

  PanelPtr logPanel( new Panel(logConWidth, logConHeight) );
  logPanel->setPosition(0, gloScreenHeight - logConHeight);
  logPanel->addWidget(_log);

  _widgets.push_back( logPanel );
}

void Gui::setupViewPanel()
{
  _viewList.reset( new List );
  _viewList->setPosition(2, 1);
  _viewList->setMaxSize(LogSize);

  PanelPtr viewPanel( new Panel(viewConWidth, viewConHeight) );
  viewPanel->setPosition(logConWidth, gloScreenHeight - viewConHeight);
  viewPanel->addWidget(_viewList);

  _widgets.push_back( viewPanel );
}

void Gui::message(std::string msg, TCODColor color)
{
  _log->push( ColoredString(msg, color) );
}

void Gui::render()
{
  std::for_each(_widgets.begin(), _widgets.end(), [](WidgetPtr w){ w->render(*TCODConsole::root);});
}

void Gui::setViewList(const std::vector<ColoredString> &items)
{
  _viewList->clear();
  for(auto e = items.begin(); e != items.end(); ++e)
  {
    if ( _viewList->size() == _viewList->getMaxSize() -1 )
    {
      _viewList->push( ColoredString("<more>", e->color) );
      break;
    }
    _viewList->push(*e);
  }
}

void Gui::setHpBar(float value, float maxValue)
{
  _hpBar->setValue(value);
  _hpBar->setMaxValue(maxValue);
}

void Gui::setPlayerName(std::string name)
{
  _playerName->setValue(name);
}

}}
