#ifndef PICKABLE_H
#define PICKABLE_H

#include <vector>
#include <actor_feature.h>
#include <item_slot_type.h>
#include <pickable_category.h>
#include <target_type.h>
#include <target.h>
#include <damage.h>

namespace amarlon {

class Actor;
class Effect;
class Pickable;
class Effect;
typedef std::shared_ptr<Actor>    ActorPtr;
typedef std::shared_ptr<Pickable> PickablePtr;
typedef std::shared_ptr<Effect>   EffectPtr;

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

  virtual TargetType getTargetType() const;
  virtual bool use(ActorPtr executor, const Target& target);
  virtual int getUsesCount() const;
  ActorPtr spilt(int amount);

  int getAmount() const;
  void setAmount(int getAmount);

  bool isStackable() const;
  EffectPtr getEffect() const;
  void setEffect(EffectPtr getEffect);

  ItemSlotType getItemSlot() const;
  void setItemSlot(const ItemSlotType &getItemSlot);
  bool isEquippable();

  PickableCategory getCategory() const;
  void setCategory(const PickableCategory &getCategory);

  Damage getDamage() const;
  int getArmorClass() const;
  int getWeight() const;
  int getPrice() const;

  virtual std::string getDescription();

private:
  bool _stackable;
  int _amount;
  EffectPtr _effect;
  ItemSlotType _itemSlot;
  PickableCategory _category;  
  int _armorClass;
  int _weight;
  int _price;
  int _usesCount;
  TargetType _targetType;
  Damage _damage;

};

typedef std::shared_ptr<Pickable> PickablePtr;

}

#endif // PICKABLE_H
