#ifndef PICKABLE_H
#define PICKABLE_H

#include <vector>
#include "data_gateways/actor_descriptions.h"
#include "actor/actor_features/actor_feature.h"
#include "actor/actor_features/wearer/item_slot_type.h"
#include "actor/actor_features/pickable_category.h"

namespace amarlon {

class Actor;
class Effect;

class Pickable : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Pickable(bool stackable = false, int amount = 1);
  virtual ~Pickable();

  static Pickable* create(Description* dsc);

  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeature* clone();
  virtual bool isEqual(ActorFeature *rhs);

  virtual bool use(Actor *executor, std::vector<Actor *> targets);
  virtual int getUsesCount() const;
  Actor* spilt(int amount);

  int getAmount() const;
  void setAmount(int getAmount);

  bool isStackable() const;
  Effect *getEffect() const;
  void setEffect(Effect *getEffect);

  ItemSlotType getItemSlot() const;
  void setItemSlot(const ItemSlotType &getItemSlot);
  bool isEquippable();

  PickableCategory getCategory() const;
  void setCategory(const PickableCategory &getCategory);

private:
  bool _stackable;
  int _amount;
  Effect* _effect;
  ItemSlotType _itemSlot;
  PickableCategory _category;

};

}

#endif // PICKABLE_H
