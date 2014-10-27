#include "list.h"
#include <algorithm>

namespace amarlon { namespace gui {

List::List()
  : _fixedSize(true)
{
}

void List::render(TCODConsole &console)
{
  int row = _y;
  std::for_each(_entries.begin(), _entries.end(), [&](ColoredString& entry)
  {
    console.setDefaultForeground(entry.color);
    console.print(_x, ++row, entry.str.c_str());
  });
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
