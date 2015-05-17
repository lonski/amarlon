#include "amenu.h"
#include <amenu_item.h>
#include <numeric>
#include <apanel.h>
#include <alabel.h>
#include <message_box.h>

namespace amarlon { namespace gui {

class Header : public APanel
{
public:
  Header(const int& w, const std::string& title)
    : APanel(w, 3) //frame + label
    , _lHeader(new ALabel)

  {
    setFrameColor(TCODColor::darkYellow);

    _lHeader->setPosition(2,1);
    _lHeader->setValue(title);

    addWidget(_lHeader);
  }

private:
  ALabelPtr _lHeader;

};

typedef std::shared_ptr<Header> HeaderPtr;

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

  sortByCategory();

  std::string currentCategory = "";
  for( auto item : _items )
  {    
    std::string category = item->getProperty<std::string>("category");
    if ( category != currentCategory )
    {
      Header categoryHeader( getWidth() , category );
      categoryHeader.setPosition( x - 1, y );
      categoryHeader.render(console);
      y += categoryHeader.getHeight();
      currentCategory = category;
    }

    item->setPosition(x, y);
    item->render(console);
    y += item->getHeight();
  }
}

void AMenu::sortByCategory()
{
  std::sort(_items.begin(), _items.end(), [](AMenuItemPtr l, AMenuItemPtr r)
  {
    return l->getProperty<std::string>("category") < r->getProperty<std::string>("category");
  });
}

AMenu::ItemsIterator AMenu::findSelectedItem()
{
  return std::find_if(_items.begin(), _items.end(), [](AMenuItemPtr i){ return i->isSelected(); } );
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

bool AMenu::isAutosized() const
{
  return _autosize;
}

void AMenu::setAutosize(bool autosize)
{
  _autosize = autosize;
}


}}
