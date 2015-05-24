#ifndef UNEQUIP_ACTION_H
#define UNEQUIP_ACTION_H

#include <memory>
#include <actor_action.h>
#include <item_slot_type.h>

namespace amarlon {

enum class UnEquipResult
{
  Ok,
  InventoryFull,
  NotEquipped,
  Nok
};

class UnEquipAction : public ActorAction
{
public:
  UnEquipAction(ActorPtr toUnEquip);
  UnEquipAction(ItemSlotType slot);
  virtual ~UnEquipAction();

  virtual bool perform(ActorPtr performer);
  virtual ActorActionUPtr clone();
  UnEquipResult getResult() const;

private:
  ActorPtr _toUnEquip;
  ActorPtr _performer;
  UnEquipResult _result;
  ItemSlotType _slot;

  void aquireItemSlotType();

};

typedef std::shared_ptr<UnEquipAction> UnEquipActionPtr;
typedef std::unique_ptr<UnEquipAction> UnEquipActionUPtr;

}

#endif // UNEQUIP_ACTION_H
