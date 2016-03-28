#ifndef BODY_SLOT_H
#define BODY_SLOT_H

#include <iostream>
#include <apanel.h>
#include <amenu_item.h>

namespace amarlon { namespace gui {

class ALabel;
class ABar;

typedef std::shared_ptr<ALabel> ALabelPtr;
typedef std::shared_ptr<ABar>   ABarPtr;

class ASlotMenuItem : public AMenuItem
{
public:
  ASlotMenuItem(int width = 10,
                const std::string& name = "",
                const std::string& value = "",
                const std::string& separator=":",
                TCODColor color = TCODColor::darkYellow );

  virtual void render(TCODConsole& console);

  virtual void select();
  virtual void deselect();
  virtual bool isSelected() const;

  virtual TCODColor getColor() const;
  virtual void setColor(const TCODColor&);

  virtual TCODColor getNameColor() const;
  virtual void setNameColor(const TCODColor&c);

  virtual std::string getValue() const;
  virtual void setValue(const std::string& value);

  virtual void setName(const std::string& name);
  virtual std::string getName();

  virtual void setHeight(int height);
  virtual void setWidth(int width);

  virtual int getHeight() const;
  virtual int getWidth() const;

private:
  APanel _panel;
  ABarPtr _background;
  ALabelPtr _slotName;
  ALabelPtr _slotValue;
  bool _selected;

  void InitalizeNameLabel(const std::string &name);
  void initalizeValueLabel(const std::string &value);
  void initalizeSeparator(const std::string &s);
  void initalizeBackground();

};

typedef std::shared_ptr<ASlotMenuItem> ASlotMenuItemPtr;

}}

#endif // BODY_SLOT_H
