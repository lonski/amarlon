#ifndef AMENU_H
#define AMENU_H

#include <memory>
#include <vector>
#include <algorithm>
#include <libtcod.hpp>
#include <awidget.h>
#include <amenu_item.h>
#include <alabel_menu_item.h>

namespace amarlon { namespace gui {

class AMenu : public AWidget
{
public:
  typedef std::vector<AMenuItemPtr>::iterator ItemsIterator;
  typedef std::vector<AMenuItemPtr>::const_iterator ConstItemsIterator;
  
  AMenu();
  virtual ~AMenu();

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

  ConstItemsIterator begin() const { return _items.begin(); }
  ConstItemsIterator end() const { return _items.end(); }

  bool isAutosized() const;
  void setAutosize(bool autosize);

  /**
   * @brief Creates Menu Items for all given objects and fills the menu
   * @param content: vector of objects to map to menu items
   * @param value_fun: a function to be called on object to get value to display on menu item
   * @param category_fun: a function to be called on object to get its category, needed if
   *        user wants to display items under their categories
   */
  template<typename T, typename MenuItemType = ALabelMenuItem>
  void fill(std::vector<std::shared_ptr<T>> content,
            std::function<std::string(std::shared_ptr<T>)> value_fun,
            std::function<std::string(std::shared_ptr<T>)> category_fun = [](std::shared_ptr<T>){ return "";})
  {    
    removeAllItems();
    for(auto t : content)
    {
        AMenuItemPtr mItem( new MenuItemType );
        mItem->setValue( value_fun(t) );
        mItem->setObject<T>(t);
        mItem->setProperty<std::string>( "category", category_fun ? category_fun(t) : "" );
        addItem(mItem);
    }
  }

protected:
  std::vector<AMenuItemPtr> _items;
  bool _autosize;
  int _width;
  int _height;

private:
  int calculateWidth() const;
  void selectFirst();
  void sortByCategory();
  ItemsIterator findSelectedItem();

};

typedef std::shared_ptr<AMenu> AMenuPtr;

}}

#endif // AMENU_H
