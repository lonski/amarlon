#ifndef BODY_SLOT_H
#define BODY_SLOT_H

#include <Gui/Widget/panel.h>
#include <Gui/Widget/label.h>

namespace amarlon { namespace gui {

class BodySlot : public Panel
{
public:
  BodySlot(int width, const std::string& name = "");

  void setSlotName(const std::string& name);
  void setSlotValue(const std::string& value);

  void InitalizeNameLabel(const std::string &name);
  void initalizeValueLabel();
  void initalizeSeparator();
private:
  LabelPtr _slotName;
  LabelPtr _slotValue;

};

typedef std::shared_ptr<BodySlot> BodySlotPtr;

}}

#endif // BODY_SLOT_H
