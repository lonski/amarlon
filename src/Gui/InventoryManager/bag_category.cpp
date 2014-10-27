#include "bag_category.h"

namespace amarlon { namespace gui {

BagCategory::BagCategory(int width, const std::string &title)
  : _main( new Panel(width, 3) ) //3 for the header
  , _header( new Panel( _main->getWidth(), _main->getHeight() ))
  , _itemColor(TCODColor::lightChartreuse)
{
  _main->setFrame(false);

  initalizeHeader(title);
}

void BagCategory::initalizeHeader(const std::string &title)
{
  _header->setFrameColor(TCODColor::darkYellow);
  _main->addWidget(_header);

  Label* lHeader = new Label;
  lHeader->setPosition(2,1);
  lHeader->setValue(title);
  _header->addWidget(lHeader);
}

void BagCategory::addItem(const std::string &name)
{
  LabelPtr newItem( new Label );
  newItem->setValue(name);
  newItem->setColor(_itemColor);
  newItem->setPosition(2, _header->getHeight() + _menuItems.size());
  _main->setHeight( _main->getHeight() + 1 );

  _main->addWidget( newItem );
  _menuItems.push_back( newItem );
}

void BagCategory::select(size_t index)
{
  if ( index < _menuItems.size())
  {
    LabelPtr item = _menuItems[index];
    item->setBgcolor(_itemColor);
    item->setColor( TCODColor::black );
  }
}

void BagCategory::unselect(size_t index)
{
  if ( index < _menuItems.size())
  {
    LabelPtr item = _menuItems[index];
    item->setBgcolor( TCODColor::black );
    item->setColor( _itemColor );
  }
}

void BagCategory::render(TCODConsole &console)
{
  _main->render(console);
}

void BagCategory::setPosition(int x, int y)
{
  _main->setPosition(x, y);
}

int BagCategory::getX() const
{
  return _main->getX();
}

int BagCategory::getY() const
{
  return _main->getY();
}

int BagCategory::getHeight() const
{
  return _main->getHeight();
}

}}
