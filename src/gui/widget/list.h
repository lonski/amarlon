#ifndef LIST_H
#define LIST_H

#include <list>
#include <libtcod.hpp>
#include <gui/widget/widget.h>
#include <utils/colored_string.h>

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

  bool isFixedSize() const;
  void setFixedSize(bool fixedSize);

private:
  size_t _maxSize;
  bool _fixedSize;
  std::list<ColoredString> _entries;

};

typedef std::shared_ptr<List> ListPtr;

}}

#endif // LIST_H
