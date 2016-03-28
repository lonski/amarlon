#include "alist.h"
#include <algorithm>

namespace amarlon { namespace gui {

AList::AList()
  : _autosize(true)
  , _width(0)
  , _height(0)  
{
}

void AList::render(TCODConsole &console)
{
  //TODO: disabled autosize - print only fixed aount of entries
  //at the momment disabled autosize is usable to keep the fixed area repainted every time
  int yPos = getY();
  for ( auto entry : _entries)
  {
    console.setDefaultForeground(entry.color);
    console.print(getX(), ++yPos, entry.str.c_str());
  }
}

void AList::clear()
{
  _entries.clear();
}

size_t AList::size() const
{
  return _entries.size();
}

AList::iterator AList::begin()
{
  return _entries.begin();
}

AList::iterator AList::end()
{
  return _entries.end();
}

bool AList::isAutosized() const
{  
  return _autosize;
}

void AList::setAutosize(bool autosize)
{  
  _autosize = autosize;
}

int AList::getWidth() const
{
  return _autosize ? calculateMaxWidth() : _width;
}

size_t AList::calculateMaxWidth() const
{
  size_t maxWidth = 0;
  for ( auto entry : _entries)
  {
    maxWidth = std::max( maxWidth, entry.str.size() );
  }
  return maxWidth;
}

int AList::getHeight() const
{
  return _autosize ? _entries.size() : _height;
}

void AList::setWidth(int width)
{
  _width = width;
}

void AList::setHeight(int height)
{
  _height = height;
}

void AList::pushBack(const ColoredString& entry)
{
  _entries.push_back(entry);
}

void AList::pushFront(const ColoredString &entry)
{
  _entries.push_front(entry);
}

void AList::popBack()
{
  _entries.pop_back();
}

void AList::popFront()
{
  _entries.pop_front();
}

}}

