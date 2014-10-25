#ifndef LIST_H
#define LIST_H

#include <list>
#include "widget.h"
#include "Utils/colored_string.h"
#include "libtcod.hpp"

namespace amarlon { namespace gui {

class List : public Widget
{
public:
  List();
  virtual ~List() {}

  virtual void render(TCODConsole& console);

  void clear();
  size_t size();
  void push(ColoredString entry);

  size_t getMaxSize() const;
  void setMaxSize(const size_t &getMaxSize);

private:
  size_t _maxSize;
  std::list<ColoredString> _entries;

};

}}

#endif // LIST_H
