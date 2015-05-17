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
class Pickable;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Pickable> PickablePtr;

class Pickable : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Pickable(bool stackable = false, int amount = 1);
  virtual ~Pickable();

  static PickablePtr create(DescriptionPtr dsc);

  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);

  virtual bool use(ActorPtr executor, std::vector<ActorPtr > targets);
  virtual int getUsesCount() const;
  ActorPtr spilt(int amount);

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

typedef std::shared_ptr<Pickable> PickablePtr;

}

#endif // PICKABLE_H
