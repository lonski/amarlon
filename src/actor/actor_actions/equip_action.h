#ifndef EQUIP_ACTION_H
#define EQUIP_ACTION_H

#include <memory>
#include <actor_action.h>
#include <item_slot_type.h>

namespace amarlon {

enum class EquipResult
{
  Ok,
  AlreadyEquiped,
  NoProperSlot,
  Nok
};

class EquipAction : public ActorAction
{
public:
  EquipAction(ActorPtr toEquip);
  virtual ~EquipAction();

  virtual bool perform(ActorPtr performer);
  EquipResult getResult() const;

private:
  ActorPtr _toEquip;
  ActorPtr _performer;
  EquipResult _result;

  ItemSlotType aquireItemSlotType();
  void removeFromInventory();

};

typedef std::shared_ptr<EquipAction> EquipActionPtr;

}

#endif // EQUIP_ACTION_H
