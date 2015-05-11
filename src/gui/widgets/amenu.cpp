#include "amenu.h"
#include <amenu_item.h>
#include <algorithm>

namespace amarlon { namespace gui {

AMenu::AMenu()
  : _autosize(true)
  , _width(0)
  , _height(0)
{
}

AMenu::~AMenu()
{
}

void AMenu::addItem(AMenuItemPtr item)
{
  _items.push_back( item );
}

bool AMenu::removeItem(AMenuItemPtr item)
{
  auto iter = std::find( _items.begin(), _items.end(), item );
  if ( iter != _items.end() )
  {
    _items.erase( iter );
    return true;
  }
  return false;
}

AMenuItemPtr AMenu::getSelectedItem()
{
  auto iter = findSelectedItem();
  return iter != _items.end() ? *iter : AMenuItemPtr();
}

void AMenu::removeAllItems()
{
  _items.clear();
}

void AMenu::selectNext()
{
  auto iter = findSelectedItem();
  if ( iter != _items.end() )
  {
    (*iter)->deselect();
    iter = ( iter == _items.end() - 1 ) ? _items.begin() : std::next(iter);
    (*iter)->select();
  }
  else
  {
    selectFirst();
  }
}

void AMenu::selectPrevious()
{
  auto iter = findSelectedItem();
  if ( iter != _items.end() )
  {
    (*iter)->deselect();
    iter =  (iter == _items.begin() ) ? _items.end() - 1 : std::prev(iter);
    (*iter)->select();
  }
  else
  {
    selectFirst();
  }
}

void AMenu::deselect()
{
  auto item = getSelectedItem();
  if ( item )
  {
    item->deselect();
  }
}

void AMenu::select(AMenuItemPtr item)
{
  if ( auto selected = getSelectedItem() )
  {
    selected->deselect();
  }

  if ( std::find(_items.begin(), _items.end(), item) != _items.end() )
  {
    item->select();
  }
}

void AMenu::selectFirst()
{
  if ( !_items.empty() )
  {
    _items.front()->select();
  }
}

void AMenu::render(TCODConsole& console)
{
  int y = getY();
  int x = getX();

  for( auto item : _items )
  {
    item->setPosition(x, y);
    item->render(console);
    y += item->getHeight();
  }
}

int AMenu::getWidth() const
{
  return _autosize ? calculateWidth() : _width;
}

int AMenu::calculateWidth() const
{
  int w = 0;
  for ( auto i : _items )
  {
    if ( i->getWidth() > w ) w = i->getWidth();
  }
  return w;
}

int AMenu::getHeight() const
{
  return _autosize ? std::accumulate(_items.begin(), _items.end(), 0,
                                     [](int sum, AMenuItemPtr item){ return sum + item->getHeight();  } )
                   : _height;
}

void AMenu::setWidth(int width)
{
  _width = width;
}

void AMenu::setHeight(int height)
{
  _height = height;

}

size_t AMenu::getItemCount() const
{
  return _items.size();
}

}}
