#ifndef MENU_H
#define MENU_H

#include <memory>
#include <map>
#include <libtcod.hpp>
#include <gui/widget/panel.h>
#include <gui/widget/menu/menu_item.h>

namespace amarlon { namespace gui {

class Menu : public Panel
{
public:
  Menu(const int &width, const int &height);

  virtual void addItem(MenuItemPtr item);
  virtual bool removeItem(int id);
  virtual MenuItemPtr getSelectedItem();
  virtual MenuItemPtr find(int id);

  virtual void render(TCODConsole& console);
  virtual int choose(TCODConsole& console);

  virtual bool select(int index);
  virtual bool selectFirst();
  virtual int selectNext();
  virtual int selectPrevious();
  virtual int getCurrentIndex() const;
  virtual void clear();
  virtual void deactivate();
  virtual void activate();

  bool showCategories() const;
  void setShowCategories(bool showCategories);

protected:
  int _currentIndex;
  bool _showCategories;
  std::vector<MenuItemPtr> _items;

  bool cIndexIsValid();
};

typedef std::shared_ptr<Menu> MenuPtr;

}}

#endif // MENU_H
