#include "Gui.h"
#include <algorithm>
#include <iostream>
#include "Widget/panel.h"
#include "Widget/list.h"

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

  , _rightPanel( new Panel(rightConWidth, rightConHeight) )
  , _logPanel( new Panel(logConWidth, logConHeight) )
  , _log(new List)
  , _viewPanel( new Panel(viewConWidth, viewConHeight) )
  , _viewList( new List )
{
  _log->setPosition(2,1);
  _log->setMaxSize(LogSize);
  _logPanel->addWidget(_log);

  _viewList->setPosition(2, 1);
  _viewList->setMaxSize(LogSize);
  _viewPanel->addWidget(_viewList);
}

void Gui::message(std::string msg, TCODColor color)
{
  _log->push( ColoredString(msg, color) );
}

void Gui::render()
{
  renderRightPanel();
  renderMessageLog();
  renderViewPanel(std::vector<ColoredString>());
}

void Gui::renderRightPanel()
{
  _rightPanel->setPosition( gloScreenWidth - rightConWidth, 0 );
  _rightPanel->render(*TCODConsole::root);
}

void Gui::renderMessageLog()
{
  _logPanel->setPosition(0, gloScreenHeight - logConHeight);
  _logPanel->render(*TCODConsole::root);
}

void Gui::renderViewPanel(const std::vector<ColoredString> &items)
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

  _viewPanel->setPosition(logConWidth, gloScreenHeight - viewConHeight);
  _viewPanel->render(*TCODConsole::root);
}

}}
