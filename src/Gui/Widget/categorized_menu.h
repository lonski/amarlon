#ifndef CATEGORIZED_MENU_H
#define CATEGORIZED_MENU_H

#include <memory>
#include <string>
#include <Gui/Widget/panel.h>
#include <Gui/Widget/selectable_label.h>
#include <libtcod.hpp>

namespace amarlon { namespace gui {

class CategorizedMenu : public Panel
{
public:
  CategorizedMenu(const int& width, const int& height);

  /**
   * @brief adds new, selectable item to menu
   * @param displayed value of item
   * @param category to which item belongs
   * @return index of item. It is incremented index of previous item by one.
   *         First item has index of 0.
   */
  int addMenuItem(const std::string& name, const std::string& category);

  int getCurrentIndex() const;
  int selectNext();
  int selectPrevious();

  virtual void render(TCODConsole& console);

  TCODColor getItemColor() const;
  void setItemColor(const TCODColor &getItemColor);

private:
  std::vector<SelectableLabelPtr> _items;
  int _currentIndex;
  TCODColor _itemColor;

};

typedef std::shared_ptr<CategorizedMenu> CategorizedMenuPtr;

}}

#endif // CATEGORIZED_MENU_H
