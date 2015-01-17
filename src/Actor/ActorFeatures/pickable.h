#ifndef PICKABLE_H
#define PICKABLE_H

#include <vector>
#include <Actor/ActorFeatures/actor_feature.h>
#include <DataGateways/ActorDescriptions.h>
#include <Actor/ActorFeatures/wearer/item_slot_type.h>
#include <Actor/ActorFeatures/pickable_category.h>

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
  void incAmount(int inc);
  void decAmount(int dec);
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
