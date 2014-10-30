#ifndef BODY_SLOT_H
#define BODY_SLOT_H

#include <iostream>
#include <Gui/Widget/panel.h>
#include <Gui/Widget/label.h>
#include <Gui/Widget/menu/menu_item.h>
#include <Gui/Widget/bar.h>

namespace amarlon { namespace gui {

class SlotMenuItem : public MenuItem
{
public:
  SlotMenuItem(int width, const std::string& name = "");

  void setSlotName(const std::string& name);
  std::string getSlotName();

  void setValue(const std::string& value);
  std::string getValue();

  virtual void select();
  virtual void deselect();

  virtual void setHeight(int height) { _height = height; return _panel.setHeight(height); }
  virtual void setWidth(int width) { _width = width; return _panel.setWidth(width); }

  virtual void render(TCODConsole& console);

  void initalizebackground();
private:
  Panel _panel;
  BarPtr _background;
  LabelPtr _slotName;
  LabelPtr _slotValue;

  void InitalizeNameLabel(const std::string &name);
  void initalizeValueLabel();
  void initalizeSeparator();

};

typedef std::shared_ptr<SlotMenuItem> SlotMenuItemPtr;

}}

#endif // BODY_SLOT_H
