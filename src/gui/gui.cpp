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
  , logConWidth( bottomConWidth / 10 * 7 )
  , logConHeight(bottomConHeight)
  , viewConWidth(bottomConWidth / 10 * 3)
  , viewConHeight(bottomConHeight)
  , LogSize( logConHeight - 3 ) // 3 is for frame
  , _frameColor(TCODColor::darkerOrange)
{
  setupRightPanel();
  setupLogPanel();
  setupViewPanel();

  AWidget::consoleHeight = Engine::consoleHeight;
  AWidget::consoleWidth = Engine::consoleWidth;
  AWidget::screenHeight = Engine::screenHeight;
}

void Gui::setupRightPanel()
{
  APanelPtr rightPanel( new APanel(rightConWidth, rightConHeight) );
  rightPanel->setPosition( Engine::screenWidth - rightConWidth, 0 );

  //Player Name
  _playerName.reset( new ALabel );
  _playerName->setPosition(2,2);
  rightPanel->addWidget(_playerName);

  //Player level
  _playerLevel.reset( new ALabel );
  _playerLevel->setPosition(2, _playerName->getY() + 2);
  rightPanel->addWidget(_playerLevel);

  //HP Bar
  _hpBar.reset( new ABar );
  _hpBar->setPosition(2,_playerLevel->getY() + 2);
  _hpBar->setName("HP");
  _hpBar->setDisplayValues(false);
  _hpBar->setWidth( rightPanel->getWidth() - 4 );
  rightPanel->addWidget(_hpBar);

  //Exp Bar
  _expBar.reset( new ABar );
  _expBar->setPosition(2, _hpBar->getY() + 4 );
  _expBar->setName("XP");
  _expBar->setDisplayValues(false);
  _expBar->setBgColor(TCODColor::darkestGreen);
  _expBar->setFgColor(TCODColor::darkGreen);
  _expBar->setWidth( rightPanel->getWidth() - 4 );
  rightPanel->addWidget(_expBar);

  //Status Effects
  _effects.reset( new AList );
  _effects->setPosition( 2, _expBar->getY() + 4 );
  _effects->setWidth( rightPanel->getWidth() - 4 );
  rightPanel->addWidget( _effects );

  _widgets.push_back( rightPanel );
}

void Gui::setupLogPanel()
{
  _log.reset(new AList);
  _log->setPosition(2,1);

  APanelPtr logPanel( new APanel(logConWidth, logConHeight) );
  logPanel->setTitle("Log");
  logPanel->setPosition(0, Engine::screenHeight - logConHeight);
  logPanel->addWidget(_log);

  _widgets.push_back( logPanel );
}

void Gui::setupViewPanel()
{
  _viewList.reset( new AList );
  _viewList->setPosition(2, 1);

  APanelPtr viewPanel( new APanel(viewConWidth, viewConHeight) );
  viewPanel->setTitle("Items on ground");
  viewPanel->setPosition(logConWidth, Engine::screenHeight - viewConHeight);
  viewPanel->addWidget(_viewList);

  _widgets.push_back( viewPanel );
}

void Gui::message(std::string msg, TCODColor color)
{
  if ( _log->size() == LogSize ) _log->popFront();
  _log->pushBack( ColoredString(msg, color) );
}

void Gui::clearLog()
{
  _log->clear();
}

void Gui::setStatusMessage(const std::string &status)
{
  TCODConsole* console = Engine::instance().getConsole();

  if ( console )
  {
    console->print(
      (Engine::consoleWidth - status.size()) / 2,
      1,
      status.c_str()
    );
  }
}

void Gui::clearStatusMessage()
{
  setStatusMessage("");
}

void Gui::render()
{
  TCODConsole* console = Engine::instance().getConsole();

  if ( console )
  {
    std::for_each(_widgets.begin(), _widgets.end(), [console](AWidgetPtr w){
      w->render(*console);
    });
  }
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

void Gui::setEffectsList(const std::vector<ColoredString> &items)
{
  _effects->clear();
  _effects->pushBack(ColoredString("--- Effects: ---", TCODColor::brass));
  _effects->pushBack(ColoredString(" "));

  for(auto e : items)
  {
    _effects->pushBack(e);
  }
}

void Gui::setHpBar(float value, float maxValue)
{
  _hpBar->setValue(value);
  _hpBar->setMaxValue(maxValue);
}

void Gui::setExpBar(float value, float maxValue)
{
  _expBar->setValue(value);
  _expBar->setMaxValue(maxValue);
}

void Gui::setPlayerName(std::string name)
{
  _playerName->setValue(name);
}

void Gui::setPlayerLevel(std::string level)
{
  _playerLevel->setValue("Level: " + level);
}

}}

