#ifndef WEARER_SERIALIZER_H
#define WEARER_SERIALIZER_H

#include <memory>
#include <actor_feature_serializer.h>
#include <effect_serializer.h>
#include <item_slot_type.h>

namespace amarlon {

class Wearer;
typedef std::shared_ptr<Wearer> WearerPtr;

class WearerSerializer : public ActorFeatureSerializer
{
public:
  WearerSerializer();
  WearerSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~WearerSerializer();

  virtual bool serialize(ActorFeaturePtr af);

private:
  rapidxml::xml_node<>* _wearerNode;
  WearerPtr _wearer;

  void serializeItemSlots();
  void serializeEquippedItem(ItemSlotType slot, rapidxml::xml_node<>* slotNode);

};

}


#endif // WEARER_SERIALIZER_H
