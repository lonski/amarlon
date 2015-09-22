#include "apanel.h"
#include <algorithm>

namespace amarlon { namespace gui {

APanel::APanel(int w, int h)
  : _frame(true)
  , _frameColor(TCODColor::darkerOrange)
  , _titleColor(TCODColor::lighterOrange)
  , _panelConsole( new TCODConsole(w, h) )
{
}

APanel::~APanel()
{
}

void APanel::render(TCODConsole &console)
{
  initPanelConsole();
  renderFrame();
  renderWidgets();

  TCODConsole::blit(_panelConsole.get(), 0, 0, _panelConsole->getWidth(), _panelConsole->getHeight(), &console, getX(), getY() );
}

void APanel::initPanelConsole()
{
  _panelConsole->setDefaultBackground(TCODColor::black);
  _panelConsole->rect( 0 , 0 , _panelConsole->getWidth(), _panelConsole->getHeight(), false,TCOD_BKGND_SET);
}

void APanel::renderFrame()
{
  if ( _frame )
  {
    _panelConsole->setDefaultForeground(_frameColor);
    _panelConsole->setDefaultBackground(_titleColor);
    _panelConsole->printFrame(0, 0, _panelConsole->getWidth(), _panelConsole->getHeight(), true, TCOD_BKGND_DEFAULT, _title.empty() ? NULL : _title.c_str() );
  }
}

void APanel::renderWidgets()
{
  std::for_each(_widgets.begin(), _widgets.end(), [&](AWidgetPtr w){ w->render(*_panelConsole); });
}

void APanel::addWidget(AWidget *widget)
{
  _widgets.push_back( AWidgetPtr(widget) );
}

void APanel::addWidget(const AWidgetPtr& widget)
{
  _widgets.push_back( widget );
}

std::string APanel::getTitle() const
{
  return _title;
}

void APanel::setTitle(const std::string &title)
{
  _title = title;
}
TCODColor APanel::getTitleColor() const
{
  return _titleColor;
}

void APanel::setTitleColor(const TCODColor &titleColor)
{
  _titleColor = titleColor;
}
bool APanel::isFramed() const
{
    return _frame;
}

void APanel::setFrame(bool frame)
{
    _frame = frame;
}
TCODColor APanel::getFrameColor() const
{
  return _frameColor;
}

void APanel::setFrameColor(const TCODColor &frameColor)
{
  _frameColor = frameColor;
}

void APanel::setWidth(int width)
{
  _panelConsole.reset( new TCODConsole(width, _panelConsole->getHeight()) );
}

void APanel::setHeight(int height)
{
  _panelConsole.reset( new TCODConsole(_panelConsole->getWidth(), height) );
}

int APanel::getWidth() const
{
  return _panelConsole->getWidth();
}

int APanel::getHeight() const
{
  return _panelConsole->getHeight();
}

void APanel::removeAllWidgets()
{
  _widgets.clear();
}

}}

