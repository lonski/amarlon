#include "categorized_menu.h"
#include <algorithm>

namespace amarlon { namespace gui {

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

CategorizedMenu::CategorizedMenu(const int &width, const int &height)
  : Panel(width, height)
  , _currentIndex(-1)
  , _itemColor(TCODColor::lightChartreuse)
{
}

int CategorizedMenu::addMenuItem(const std::string &name, const std::string &category)
{
  SelectableLabelPtr newItem( new SelectableLabel );
  newItem->setValue(name);
  newItem->setTag("category",category);
  newItem->setColor(_itemColor);

  _items.push_back( newItem );

  return _items.size() - 1;
}

int CategorizedMenu::getCurrentIndex() const
{
  return _currentIndex;
}

int CategorizedMenu::selectNext()
{
  if ( _items.size() > 0 )
  {
    //deselect current item
    if ( _currentIndex >= 0 && _currentIndex < (int)_items.size() ) _items[_currentIndex]->deselect();

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

int CategorizedMenu::selectPrevious()
{
  if ( _items.size() > 0 )
  {
    //deselect current item
    if ( _currentIndex >= 0 && _currentIndex < (int)_items.size() ) _items[_currentIndex]->deselect();

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

void CategorizedMenu::render(TCODConsole &console)
{
  int margin = isFramed() ? 2 : 0;
  int itemWidth = getWidth() - 2*margin;
  int row = margin;

  std::sort(_items.begin(), _items.end(), [](SelectableLabelPtr l, SelectableLabelPtr r)
  {
    return l->getTag("category") < r->getTag("category");
  });

  std::string cat;
  for(size_t i = 0; i < _items.size(); ++i)
  {
    SelectableLabelPtr item = _items[i];
    std::string itemCat = item->getTag("category");
    if ( itemCat != cat )
    {
      cat = itemCat;
      headerPtr newCatPanel( new Header(itemWidth, cat ) );
      newCatPanel->setPosition( margin, row );
      row += newCatPanel->getHeight();

      addWidget( newCatPanel );
    }

    item->setPosition(margin + 1, row++);
    addWidget( item );
  }

  Panel::render(console);
}
TCODColor CategorizedMenu::getItemColor() const
{
  return _itemColor;
}

void CategorizedMenu::setItemColor(const TCODColor &itemColor)
{
  _itemColor = itemColor;

  std::for_each(_items.begin(), _items.end(), [&](SelectableLabelPtr item)
  {
    item->setColor(_itemColor);
  });
}


  }}
