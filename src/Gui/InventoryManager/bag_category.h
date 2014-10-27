#ifndef BAG_CATEGORY_H
#define BAG_CATEGORY_H

#include <Gui/Widget/panel.h>
#include <Gui/Widget/label.h>

namespace amarlon { namespace gui {

class BagCategory : public Widget
{
public:
  BagCategory(int width, const std::string& title = "");

  virtual void setPosition(int x, int y);
  virtual int getX() const;
  virtual int getY() const;
  int getHeight() const;

  void addItem(const std::string& name);
  void select(size_t index);
  void unselect(size_t index);

  void render(TCODConsole& console);

public:
  PanelPtr _main;
  PanelPtr _header;
  std::vector<LabelPtr> _menuItems;

  TCODColor _itemColor;

  void initalizeHeader(const std::string &title);
};

}}

#endif // BAG_CATEGORY_H
