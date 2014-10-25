#include "panel.h"
#include <algorithm>

namespace amarlon { namespace gui {

Panel::Panel(const int& w, const int& h)
  : _width(w)
  , _height(h)
  , _frame(true)
  , _frameColor(TCODColor::darkerOrange)
  , _panel(new TCODConsole(_width, _height))

{
}

void Panel::render(TCODConsole& console)
{
  if (_frame)
  {
    _panel->setDefaultForeground(_frameColor);
    _panel->printFrame(0, 0, _width, _height, true, TCOD_BKGND_DEFAULT);
  }

  std::for_each(_widgets.begin(), _widgets.end(), [&](WidgetPtr w){ w->render(*_panel); });

  TCODConsole::blit(_panel.get(), 0, 0, _width, _height, &console, _x, _y );
}

void Panel::addWidget(Widget *widget)
{
  _widgets.push_back( WidgetPtr(widget) );
}

void Panel::addWidget(WidgetPtr widget)
{
  _widgets.push_back( widget );
}

int Panel::getWidth() const
{
  return _width;
}

void Panel::setWidth(int width)
{
  _width = width;
}
int Panel::getHeight() const
{
  return _height;
}

void Panel::setHeight(int height)
{
  _height = height;
}

}}
