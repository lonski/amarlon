#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <memory>
#include <iostream>
#include <Gui/Widget/widget.h>

namespace amarlon { namespace gui {

class MenuItem : public Widget
{
public:
  MenuItem() : _selected(false) {}
  virtual ~MenuItem() {}

  virtual void select() = 0;
  virtual void deselect() = 0;
  virtual bool selected() const
  {
    return _selected;
  }

protected:
  bool _selected;

};

typedef std::shared_ptr<MenuItem> MenuItemPtr;

}}

#endif // MENU_ITEM_H
