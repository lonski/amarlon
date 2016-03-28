#ifndef EQUIP_ACTION_H
#define EQUIP_ACTION_H

#include <memory>
#include <actor_action.h>
#include <item_slot_type.h>

namespace amarlon {

class EquipAction : public ActorAction
{
public:
  EquipAction(ActorPtr toEquip);
  virtual ~EquipAction();

  virtual ActorActionResult perform(ActorPtr performer);
  virtual ActorActionUPtr clone();

private:
  ActorPtr _toEquip;
  ActorPtr _performer;

  ItemSlotType aquireItemSlotType();
  void removeFromInventory();

};

typedef std::shared_ptr<EquipAction> EquipActionPtr;
typedef std::unique_ptr<EquipAction> EquipActionUPtr;

}

#endif // EQUIP_ACTION_H
