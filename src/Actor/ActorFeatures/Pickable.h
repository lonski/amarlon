#ifndef PICKABLE_H
#define PICKABLE_H

#include <vector>
#include "ActorFeature.h"
#include "DataGateways/ActorDescriptions.h"
#include "Wearer/item_slot_type.h"

namespace amarlon {

class Actor;
class Effect;

class Pickable : public ActorFeature
{
public:
  Pickable(bool stackable = false, int amount = 1);
  virtual ~Pickable() {}
  static Pickable* create(const PickableDescription& dsc);

  virtual ActorFeature* clone();
  virtual bool isEqual(ActorFeature *rhs);

  virtual bool use(Actor *executor, std::vector<Actor *> targets);
  virtual int getUsesCount() const;
  Actor* spilt(int amount);

  int getAmount() const;
  void setAmount(int getAmount);
  void incAmount(int inc);
  bool isStackable() const;
  Effect *getEffect() const;
  void setEffect(Effect *getEffect);

  ItemSlotType getItemSlot() const;
  void setItemSlot(const ItemSlotType &getItemSlot);

private:
  bool _stackable;
  int _amount;
  Effect* _effect;
  ItemSlotType _itemSlot;

};

}

#endif // PICKABLE_H
