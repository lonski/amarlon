#include "gui.h"
#include <algorithm>
#include <iostream>
#include <engine.h>
#include <abar.h>
#include <alist.h>
#include <alabel.h>
#include <apanel.h>

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
  APanelPtr rightPanel( new APanel(rightConWidth, rightConHeight) );
  rightPanel->setPosition( Engine::screenWidth - rightConWidth, 0 );

  _playerName.reset( new ALabel );
  _playerName->setPosition(2,2);
  rightPanel->addWidget(_playerName);

  _hpBar.reset( new ABar );
  _hpBar->setPosition(2,4);
  _hpBar->setName("HP");
  _hpBar->setWidth( rightPanel->getWidth() - 4 );
  rightPanel->addWidget(_hpBar);

  _widgets.push_back( rightPanel );
}

void Gui::setupLogPanel()
{
  _log.reset(new AList);
  _log->setPosition(2,1);

  APanelPtr logPanel( new APanel(logConWidth, logConHeight) );
  logPanel->setPosition(0, Engine::screenHeight - logConHeight);
  logPanel->addWidget(_log);

  _widgets.push_back( logPanel );
}

void Gui::setupViewPanel()
{
  _viewList.reset( new AList );
  _viewList->setPosition(2, 1);

  APanelPtr viewPanel( new APanel(viewConWidth, viewConHeight) );
  viewPanel->setPosition(logConWidth, Engine::screenHeight - viewConHeight);
  viewPanel->addWidget(_viewList);

  _widgets.push_back( viewPanel );
}

void Gui::message(std::string msg, TCODColor color)
{
  if ( _log->size() == LogSize ) _log->popFront();
  _log->pushBack( ColoredString(msg, color) );
}

void Gui::setStatusMessage(const std::string &status)
{
  TCODConsole::root->print(
    (Engine::consoleWidth - status.size()) / 2,
    1,
    status.c_str()
  );
}

void Gui::clearStatusMessage()
{
  setStatusMessage("");
}

void Gui::render()
{
  std::for_each(_widgets.begin(), _widgets.end(), [](AWidgetPtr w){ w->render(*TCODConsole::root);});
}

void Gui::setViewList(const std::vector<ColoredString> &items)
{
  _viewList->clear();
  for(auto e : items)
  {
    if ( _viewList->size() == LogSize - 1 )
    {
      _viewList->pushBack( ColoredString("<more>", e.color) );
      break;
    }

    _viewList->pushBack(e);
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
