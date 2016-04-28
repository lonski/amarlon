#ifndef PICKABLE_H
#define PICKABLE_H

#include <vector>
#include <actor_feature.h>
#include <item_slot_type.h>
#include <pickable_category.h>
#include <target_type.h>
#include <target.h>
#include <damage.h>
#include <item_type.h>
#include <use_type.h>
#include <spell.h>

namespace amarlon {

class Actor;
class Pickable;
struct PickableDescription;
typedef std::shared_ptr<PickableDescription> PickableDescriptionPtr;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Pickable> PickablePtr;

class Pickable : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Pickable(DescriptionPtr dsc = nullptr);
  virtual void upgrade(DescriptionPtr dsc);
  virtual DescriptionPtr toDescriptionStruct(ActorFeaturePtr cmp = nullptr);
  virtual ~Pickable();

  static PickablePtr create(DescriptionPtr dsc);
  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;
  ActorPtr spilt(int amount);

  /**
   * @brief Executes Lua script defined by scriptId.
   */
  virtual bool use(ActorPtr executor, const Target& target);

  /**
   * @brief Defines if item can be used.
   */
  virtual bool isUsable() const;

  virtual int getUsesCount() const;
  virtual void setUsesCount(int uses);

  virtual UseType getUseType() const;
  virtual void setUseType(UseType t);

  virtual TargetType getTargetType() const;
  virtual int getRange() const;
  virtual int getRadius() const;
  virtual int getScriptId() const;

  int getAmount() const;
  void setAmount(int getAmount);

  bool isStackable() const;
  void setStackable(bool stackable);

  ItemSlotType getItemSlot() const;
  void setItemSlot(const ItemSlotType &getItemSlot);
  bool isEquippable();

  PickableCategory getCategory() const;
  void setCategory(PickableCategory getCategory);

  ItemType getItemType() const;
  void setItemType(ItemType type);

  Damage getDamage() const;
  Damage* getMutableDamage();
  void setDamage(const Damage& dmg);

  int getArmorClass() const;
  int getPrice() const;

  int getWeight() const;
  void setWeight(int weight);

  SpellPtr getSpell() const;

  virtual std::string getDescription();

  virtual void tickDay();

protected:
  void toDescriptionStruct(PickableDescriptionPtr dsc, PickablePtr cmpP = nullptr);
  void clone(Pickable* p);
  int _usesCount;

private:
  bool _stackable;
  int _amount;
  ItemSlotType _itemSlot;
  int _armorClass;
  int _weight;
  int _price;
  TargetType _targetType;
  Damage _damage;
  int _scriptId;
  ItemType _type;
  int _range;
  int _radius;
  UseType _useType;
  SpellPtr _spell;

  std::string getScriptPath() const;

};

typedef std::shared_ptr<Pickable> PickablePtr;

}

#endif // PICKABLE_H
