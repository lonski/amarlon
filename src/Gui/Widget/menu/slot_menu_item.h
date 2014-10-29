#ifndef BODY_SLOT_H
#define BODY_SLOT_H

#include <Gui/Widget/panel.h>
#include <Gui/Widget/label.h>
#include <Gui/Widget/menu/menu_item.h>

namespace amarlon { namespace gui {

class SlotMenuItem : public MenuItem
{
public:
  SlotMenuItem(int width, const std::string& name = "");

  void setSlotName(const std::string& name);
  std::string getSlotName();

  void setSlotValue(const std::string& value);
  std::string getSlotValue();

  virtual void select();
  virtual void deselect();
  virtual int getHeight() { return _panel.getHeight(); }

  virtual void render(TCODConsole& console);

private:
  Panel _panel;
  TCODColor _frameColorTemp;
  LabelPtr _slotName;
  LabelPtr _slotValue;

  void InitalizeNameLabel(const std::string &name);
  void initalizeValueLabel();
  void initalizeSeparator();

};

typedef std::shared_ptr<SlotMenuItem> SlotMenuItemPtr;

}}

#endif // BODY_SLOT_H
