#include "ahorizontal_menu.h"

namespace amarlon { namespace gui {

AHorizontalMenu::AHorizontalMenu()
{
}

AHorizontalMenu::~AHorizontalMenu()
{
}

void AHorizontalMenu::render(TCODConsole &console)
{
  int y = getY();
  int x = getX();

  for( auto item : _items )
  {
    item->setPosition(x, y);
    item->render(console);
    x += item->getWidth();
  }
}

int AHorizontalMenu::getWidth() const
{
  return _autosize ? std::accumulate(_items.begin(), _items.end(), 0,
                                     [](int sum, AMenuItemPtr item){ return sum + item->getWidth();  } )
                   : _width;
}

int AHorizontalMenu::getHeight() const
{
  return _autosize ? calculateHeight() : _height;
}

int AHorizontalMenu::calculateHeight() const
{
  int h = 0;
  for ( auto i : _items )
  {
    if ( i->getHeight() > h ) h = i->getHeight();
  }
  return h;
}

}}
