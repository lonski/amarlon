#ifndef AMENU_H
#define AMENU_H

#include <memory>
#include <vector>
#include <algorithm>
#include <libtcod.hpp>
#include <awidget.h>
#include <amenu_item.h>

namespace amarlon { namespace gui {

class AMenu : public AWidget
{
public:
  AMenu();
  ~AMenu();

  virtual void addItem(AMenuItemPtr item);
  virtual bool removeItem(AMenuItemPtr item);
  virtual AMenuItemPtr getSelectedItem();
  virtual void removeAllItems();

  virtual void selectNext();
  virtual void selectPrevious();
  virtual void deselect();
  virtual void select(AMenuItemPtr item);

  virtual void render(TCODConsole& console);

  virtual int getWidth() const;
  virtual int getHeight() const;

  virtual void setWidth(int width);
  virtual void setHeight(int height);

  virtual size_t getItemCount() const;

  auto begin() const { return _items.begin(); }
  auto end() const { return _items.end(); }

private:
  std::vector<AMenuItemPtr> _items;
  bool _autosize;
  int _width;
  int _height;

  int calculateWidth() const;
  void selectFirst();
  auto findSelectedItem()
  {
    return std::find_if(_items.begin(), _items.end(), [](auto& i){ return i->isSelected(); } );
  }

};

typedef std::shared_ptr<AMenu> AMenuPtr;

}}

#endif // AMENU_H
