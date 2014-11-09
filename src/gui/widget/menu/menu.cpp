#include "menu.h"
#include <algorithm>
#include <gui/widget/label.h>

namespace amarlon { namespace gui {

// === HEADER === //

class Header : public Panel
{
public:
  Header(const int& w, const std::string& title)
    : Panel(w, 3) //frame + label
    , _lHeader(new Label)

  {
    setFrameColor(TCODColor::darkYellow);

    _lHeader->setPosition(2,1);
    _lHeader->setValue(title);

    addWidget(_lHeader);
  }

private:
  LabelPtr _lHeader;

};

typedef std::shared_ptr<Header> HeaderPtr;
//~~~

// === MENU === //

Menu::Menu(const int &width, const int &height)
  : Panel(width, height)
  , _currentIndex(-1)
  , _showCategories(true)
{
}

void Menu::addItem(MenuItemPtr item)
{
  _items.push_back( item );
}

bool Menu::removeItem(int id)
{
  auto found = std::find_if(_items.begin(), _items.end(),
  [&id](MenuItemPtr item)
  {
    return item->getTag( "id" ) == std::to_string(id);
  });

  bool r = found != _items.end();
  if ( r )
  {
    deactivate();
    _currentIndex = -1;
    _items.erase( found );
  }

  return r;
}

MenuItemPtr Menu::getSelectedItem()
{
  MenuItemPtr r;

  if ( cIndexIsValid() )
  {
    r = _items[ _currentIndex ];
  }

  return r;
}

MenuItemPtr Menu::find(int id)
{
  auto found = std::find_if(_items.begin(), _items.end(),
  [&id](MenuItemPtr item)
  {
    return item->getTag( "id" ) == std::to_string(id);
  });

  return found == _items.end() ? MenuItemPtr() : *found;
}

void Menu::render(TCODConsole &console)
{
  removeAllWidgets();

  int margin = isFramed() ? 2 : 0;
  int itemWidth = getWidth() - 2*margin;
  int row = margin;
  int totalHeight = margin * 2;

  std::sort(_items.begin(), _items.end(), [](MenuItemPtr l, MenuItemPtr r)
  {
    return l->getTag("category") < r->getTag("category");
  });

  std::string cat;
  for(size_t i = 0; i < _items.size(); ++i)
  {
    MenuItemPtr item = _items[i];
    int extraMargin = 0;

    if ( _showCategories )
    {
      std::string itemCat = item->getTag("category");
      if ( itemCat != cat )
      {
        cat = itemCat;
        HeaderPtr newCatPanel( new Header(itemWidth, cat ) );
        newCatPanel->setPosition( margin, row );
        row += newCatPanel->getHeight();

        totalHeight += newCatPanel->getHeight();
        addWidget( newCatPanel );
      }
      if ( !itemCat.empty() ) ++extraMargin; //add extra margin for items under category
    }

    item->setPosition(margin + extraMargin, row);

    totalHeight += item->getHeight();
    addWidget( item );            
    row += item->getHeight();
  }

  if ( totalHeight > getHeight() ) setHeight( totalHeight );

  Panel::render(console);
}

int Menu::selectNext()
{
  if ( _items.size() > 0 )
  {
    //deselect current item
    if ( cIndexIsValid() ) _items[_currentIndex]->deselect();

    if ( _currentIndex + 1 < (int)_items.size() ) //select next
    {
      ++_currentIndex;
    }
    else // loop, select first
    {
      _currentIndex = 0;
    }

    _items[_currentIndex]->select();
  }

  return _currentIndex;
}

int Menu::selectPrevious()
{
  if ( _items.size() > 0 )
  {
    //deselect current item
    if ( cIndexIsValid() ) _items[_currentIndex]->deselect();

    if ( _currentIndex - 1 >= 0 ) //select prev
    {
      --_currentIndex;
    }
    else // loop, select last
    {
      _currentIndex = _items.size() - 1;
    }

    _items[_currentIndex]->select();
  }

  return _currentIndex;
}

int Menu::getCurrentIndex() const
{
  return _currentIndex;
}

void Menu::clear()
{
  if ( cIndexIsValid() ) _items[_currentIndex]->deselect();

  _items.clear();
  _currentIndex = -1;
  removeAllWidgets();
}

bool Menu::cIndexIsValid()
{
  return _currentIndex >= 0 && _currentIndex < (int)_items.size()  ;
}

void Menu::deactivate()
{
  if ( cIndexIsValid() ) _items[ _currentIndex ]->deselect();
}

void Menu::activate()
{
  if ( cIndexIsValid() )
  {
    _items[ _currentIndex ]->select();
  }
  else if ( !_items.empty() )
  {
    _currentIndex = 0;
    _items[ _currentIndex ]->select();
  }
}
bool Menu::showCategories() const
{
  return _showCategories;
}

void Menu::setShowCategories(bool showCategories)
{
  _showCategories = showCategories;
}

int Menu::choose(TCODConsole& console)
{
  int id = -1;
  TCOD_key_t key;

  while( !(key.vk == TCODK_ESCAPE) &&
         !(key.vk == TCODK_ENTER ) &&
         !(key.vk == TCODK_KPENTER) &&
         !(TCODConsole::isWindowClosed()))
  {
    render(console);
    console.flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    switch ( key.vk )
    {
      case TCODK_DOWN:
      case TCODK_KP2:
      {
        selectNext();
        break;
      }
      case TCODK_UP:
      case TCODK_KP8:
      {
        selectPrevious();
        break;
      }

      default:;
    }

  }

  if ( key.vk == TCODK_ENTER || key.vk == TCODK_KPENTER)
  {
    MenuItemPtr s = getSelectedItem();
    if ( s ) id = std::stol( s->getTag("id") );
  }

  return id;
}

bool Menu::select(int index)
{
  bool selected = false;

  std::sort(_items.begin(), _items.end(), [](MenuItemPtr l, MenuItemPtr r)
  {
    return l->getTag("category") < r->getTag("category");
  });

  for(auto i = _items.begin(); i != _items.end(); ++i) (*i)->deselect();

  _currentIndex = index;
  if ( cIndexIsValid() )
  {
    _items[ _currentIndex ]->select();
    selected = true;
  }

  return selected;
}

bool Menu::selectFirst()
{
  return select(0);
}

}}
