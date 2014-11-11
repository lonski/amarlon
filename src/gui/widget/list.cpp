#include "list.h"
#include <algorithm>

namespace amarlon { namespace gui {

List::List()
  : _maxSize(0)
  , _fixedSize(true)
{
}

void List::render(TCODConsole &console)
{
  int row = _y;
  int maxWidth = 1;

  std::for_each(_entries.begin(), _entries.end(), [&](ColoredString& entry)
  {
    if ( entry.str.size() > (unsigned)maxWidth ) maxWidth = entry.str.size();
    console.setDefaultForeground(entry.color);
    console.print(_x, ++row, entry.str.c_str());
  });

  setHeight(row);
  setWidth(maxWidth);
}

void List::clear()
{
  _entries.clear();
}

size_t List::size()
{
  return _entries.size();
}

void List::push(ColoredString entry)
{
  if ( _entries.size() == _maxSize && _fixedSize )
  {
    _entries.pop_front();
  }

  _entries.push_back(entry);
}

size_t List::getMaxSize() const
{
  return _maxSize;
}

void List::setMaxSize(const size_t &maxSize)
{
  _maxSize = maxSize;
}
bool List::isFixedSize() const
{
  return _fixedSize;
}

void List::setFixedSize(bool fixedSize)
{
  _fixedSize = fixedSize;
}


}}
