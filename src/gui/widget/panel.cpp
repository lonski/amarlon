#include "panel.h"
#include <algorithm>

namespace amarlon { namespace gui {

Panel::Panel(const int& w, const int& h)
  : Widget(w,h)
  , _frame(true)
  , _frameColor(TCODColor::darkerOrange)
  , _titleColor(TCODColor::lighterOrange)
  , _panel(new TCODConsole(_width, _height))
{
}

void Panel::render(TCODConsole& console)
{
  _panel->setDefaultBackground(TCODColor::black);
  _panel->rect( 0 , 0 , _width, _height, false,TCOD_BKGND_SET);

  if (_frame)
  {
    _panel->setDefaultForeground(_frameColor);
    _panel->setDefaultBackground(_titleColor);
    _panel->printFrame(0, 0, _width, _height, true, TCOD_BKGND_DEFAULT, _title.empty() ? NULL : _title.c_str() );
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

void Panel::removeAllWidgets()
{
  _widgets.clear();
}

void Panel::setWidth(int width)
{
  _width = width;
  _panel.reset( new TCODConsole(_width, _height) );
}

void Panel::setHeight(int height)
{
  _height = height;
  _panel.reset( new TCODConsole(_width, _height) );
}
std::string Panel::setTitle() const
{
  return _title;
}

void Panel::setTitle(const std::string &title)
{
  _title = title;
}
TCODColor Panel::getTitleColor() const
{
  return _titleColor;
}

void Panel::setTitleColor(const TCODColor &titleColor)
{
  _titleColor = titleColor;
}
bool Panel::isFramed() const
{
    return _frame;
}

void Panel::setFrame(bool frame)
{
    _frame = frame;
}
TCODColor Panel::getFrameColor() const
{
  return _frameColor;
}

void Panel::setFrameColor(const TCODColor &frameColor)
{
  _frameColor = frameColor;
}


}}
