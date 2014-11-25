#include "alist.h"
#include <algorithm>

namespace amarlon { namespace gui {

AList::AList()
  : _autosize(true)
{
}

void AList::render(TCODConsole &console)
{
  size_t maxWidth = 1;

  int yPos = _y;
  for ( auto entry : _entries)
  {
    maxWidth = std::max( maxWidth, entry.str.size() );

    console.setDefaultForeground(entry.color);
    console.print(_x, ++yPos, entry.str.c_str());
  }

  if ( _autosize )
  {
    setHeight(_entries.size());
    setWidth(maxWidth);
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
