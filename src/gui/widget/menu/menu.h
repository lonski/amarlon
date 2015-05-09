#ifndef MENU_H
#define MENU_H

#include <memory>
#include <map>
#include <libtcod.hpp>
#include <apanel.h>
#include <amenu_item.h>

namespace amarlon { namespace gui {

class Menu : public APanel
{
public:
  Menu(const int &width, const int &height);

  virtual void addItem(AMenuItemPtr item);
  virtual bool removeItem(int id);
  virtual AMenuItemPtr getSelectedItem();
  virtual AMenuItemPtr find(int id);

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
  std::vector<AMenuItemPtr> _items;

  bool cIndexIsValid();
};

typedef std::shared_ptr<Menu> MenuPtr;

}}

#endif // MENU_H
