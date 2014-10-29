#ifndef MENU_H
#define MENU_H

#include <memory>
#include <map>
#include <libtcod.hpp>
#include <Gui/Widget/panel.h>
#include <Gui/Widget/menu/menu_item.h>

namespace amarlon { namespace gui {

class Menu : public Panel
{
public:
  Menu(const int &width, const int &height);

  virtual void addItem(MenuItemPtr item);
  virtual MenuItemPtr getSelectedItem();

  virtual void render(TCODConsole& console);

  virtual int selectNext();
  virtual int selectPrevious();
  virtual int getCurrentIndex() const;
  virtual void clear();
  virtual void deactivate();
  virtual void activate();

protected:
  int _currentIndex;
  std::vector<MenuItemPtr> _items;

  bool cIndexIsValid();
};

typedef std::shared_ptr<Menu> MenuPtr;

}}

#endif // MENU_H
