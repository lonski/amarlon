#ifndef UNEQUIP_ACTION_H
#define UNEQUIP_ACTION_H

#include <memory>
#include <actor_action.h>
#include <item_slot_type.h>

namespace amarlon {

class UnEquipAction : public ActorAction
{
public:
  UnEquipAction(ActorPtr toUnEquip);
  UnEquipAction(ItemSlotType slot);
  virtual ~UnEquipAction();

  virtual ActorActionResult perform(ActorPtr performer);
  virtual ActorActionUPtr clone();

private:
  ActorPtr _toUnEquip;
  ActorPtr _performer;
  ItemSlotType _slot;

  void aquireItemSlotType();

};

typedef std::shared_ptr<UnEquipAction> UnEquipActionPtr;
typedef std::unique_ptr<UnEquipAction> UnEquipActionUPtr;

}

#endif // UNEQUIP_ACTION_H
