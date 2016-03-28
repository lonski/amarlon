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
#include <actor.pb.h>

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
  const static ActorFeature::Type FeatureType;

  static PickablePtr create(const PickableData& data);

  Pickable();
  Pickable(const Pickable& rhs);
  virtual ~Pickable();

  bool operator==(const Pickable& rhs) const;
  Pickable& operator=(const Pickable& rhs);
  virtual const PickableData& getData() const;
  virtual const ::google::protobuf::Message& getDataPolymorphic() const;

  virtual ActorFeature::Type getFeatureType() { return FeatureType; }
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
  virtual int getRange() const;
  virtual int getRadius() const;
  virtual int getScriptId() const;

  int getAmount() const;
  void setAmount(int getAmount);

  bool isStackable() const;

  ItemSlotType getItemSlot() const;
  void setItemSlot(const ItemSlotType &getItemSlot);
  bool isEquippable();

  PickableCategory getCategory() const;
  void setCategory(PickableCategory getCategory);

  ItemType getItemType() const;
  void setItemType(ItemType type);

  Damage getDamage() const;
  int getArmorClass() const;
  int getWeight() const;
  int getPrice() const;

  virtual std::string getDescription();

protected:
  PickableData _data;

  Pickable(const PickableData& data);
  std::string getScriptPath() const;

};

typedef std::shared_ptr<Pickable> PickablePtr;

}

#endif // PICKABLE_H
