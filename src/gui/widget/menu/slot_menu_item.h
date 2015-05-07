#ifndef BODY_SLOT_H
#define BODY_SLOT_H

#include <iostream>
#include <apanel.h>
#include <gui/widget/menu/menu_item.h>

namespace amarlon { namespace gui {

class ALabel;
class ABar;

typedef std::shared_ptr<ALabel> ALabelPtr;
typedef std::shared_ptr<ABar>   ABarPtr;

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

private:
  APanel _panel;
  ABarPtr _background;
  ALabelPtr _slotName;
  ALabelPtr _slotValue;

  void InitalizeNameLabel(const std::string &name);
  void initalizeValueLabel();
  void initalizeSeparator();
  void initalizebackground();

};

typedef std::shared_ptr<SlotMenuItem> SlotMenuItemPtr;

}}

#endif // BODY_SLOT_H
