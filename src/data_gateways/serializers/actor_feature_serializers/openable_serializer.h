#ifndef OPENABLE_SERIALIZER_H
#define OPENABLE_SERIALIZER_H

#include <memory>
#include <actor_feature_serializer.h>

namespace amarlon {

class Openable;
typedef std::shared_ptr<Openable> OpenablePtr;

class OpenableSerializer : public ActorFeatureSerializer
{
public:
  OpenableSerializer();
  OpenableSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~OpenableSerializer();

  /** Openable is an abstract class - here is just common serialization in protected section
   *  which should be called in each serializer for given Openable type
   */
  virtual bool serialize(ActorFeaturePtr af);

protected:
  void serializeOpenableCommonPart(rapidxml::xml_node<>* openableNode, OpenablePtr openable);

};

}

#endif // OPENABLE_SERIALIZER_H
