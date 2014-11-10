#include "gui.h"
#include <algorithm>
#include <iostream>
#include "widget/panel.h"
#include "widget/list.h"
#include "widget/bar.h"
#include "widget/label.h"
#include <engine.h>

namespace amarlon { namespace gui {

Gui::Gui()
  : rightConWidth( Engine::rightPanelWidth )
  , rightConHeight(Engine::screenHeight)
  , bottomConWidth(Engine::screenWidth - Engine::rightPanelWidth)
  , bottomConHeight(Engine::bottomPanelHeight)
  , logConWidth((bottomConWidth) / 2)
  , logConHeight(bottomConHeight)
  , viewConWidth((bottomConWidth) / 2)
  , viewConHeight(bottomConHeight)
  , LogSize( logConHeight - 3 ) // 3 is for frame
  , _frameColor(TCODColor::darkerOrange)

{
  setupRightPanel();
  setupLogPanel();
  setupViewPanel();
}

void Gui::setupRightPanel()
{
  PanelPtr rightPanel( new Panel(rightConWidth, rightConHeight) );
  rightPanel->setPosition( Engine::screenWidth - rightConWidth, 0 );

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
  logPanel->setPosition(0, Engine::screenHeight - logConHeight);
  logPanel->addWidget(_log);

  _widgets.push_back( logPanel );
}

void Gui::setupViewPanel()
{
  _viewList.reset( new List );
  _viewList->setPosition(2, 1);
  _viewList->setMaxSize(LogSize);

  PanelPtr viewPanel( new Panel(viewConWidth, viewConHeight) );
  viewPanel->setPosition(logConWidth, Engine::screenHeight - viewConHeight);
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
