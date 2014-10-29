#ifndef SELECTABLE_LABEL_H
#define SELECTABLE_LABEL_H

#include <memory>
#include <Gui/Widget/label.h>
#include <Gui/Widget/menu/menu_item.h>

namespace amarlon { namespace gui {

class LabelMenuItem : public MenuItem
{
public:
  LabelMenuItem();

  virtual void render(TCODConsole& console);

  virtual void select();
  virtual void deselect();

  std::string getValue() const;
  void setValue(const std::string &value);

  TCODColor getColor() const;
  void setColor(const TCODColor &color);

  virtual int getHeight() { return 1; }

private:
  Label _label;

};

typedef std::shared_ptr<LabelMenuItem> LabelMenuItemPtr;

}}

#endif // SELECTABLE_LABEL_H
