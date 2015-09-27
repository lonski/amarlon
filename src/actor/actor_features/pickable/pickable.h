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
class Pickable;
typedef std::shared_ptr<Actor>    ActorPtr;
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
  virtual bool isEqual(ActorFeaturePtr rhs) const;
  ActorPtr spilt(int amount);

  /**
   * @brief Executes Lua script defined by scriptId.
   */
  virtual bool use(ActorPtr executor, const Target& target);
  /**
   * @brief Defines if item can be used.
   * @return True if script id is defined and uses count != 0
   */
  virtual bool isUsable() const;
  virtual int getUsesCount() const;
  virtual TargetType getTargetType() const;
  virtual int getScriptId() const;

  int getAmount() const;
  void setAmount(int getAmount);

  bool isStackable() const;

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
  ItemSlotType _itemSlot;
  PickableCategory _category;  
  int _armorClass;
  int _weight;
  int _price;
  int _usesCount;
  TargetType _targetType;
  Damage _damage;
  int _scriptId;

  std::string getScriptPath() const;

};

typedef std::shared_ptr<Pickable> PickablePtr;

}

#endif // PICKABLE_H
