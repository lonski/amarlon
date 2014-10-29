#include "menu.h"
#include <algorithm>
#include <Gui/Widget/label.h>

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

typedef std::shared_ptr<Header> headerPtr;
//~~~

// === MENU === //

Menu::Menu(const int &width, const int &height)
  : Panel(width, height)
  , _currentIndex(-1)
{
}

void Menu::addItem(MenuItemPtr item)
{
  _items.push_back( item );
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

void Menu::render(TCODConsole &console)
{
  int margin = isFramed() ? 2 : 0;
  int itemWidth = getWidth() - 2*margin;
  int row = margin;

  std::sort(_items.begin(), _items.end(), [](MenuItemPtr l, MenuItemPtr r)
  {
    return l->getTag("category") < r->getTag("category");
  });

  std::string cat;
  for(size_t i = 0; i < _items.size(); ++i)
  {
    MenuItemPtr item = _items[i];
    std::string itemCat = item->getTag("category");
    if ( itemCat != cat )
    {
      cat = itemCat;
      headerPtr newCatPanel( new Header(itemWidth, cat ) );
      newCatPanel->setPosition( margin, row );
      row += newCatPanel->getHeight();

      addWidget( newCatPanel );
    }

    int extraMargin = (itemCat.empty() ? 0 : 1); //add extra margin for items under category
    item->setPosition(margin + extraMargin, row);

    addWidget( item );
    row += item->getHeight();
  }

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
  _items.clear();
  _currentIndex = -1;
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

}}
