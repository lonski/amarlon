#ifndef TALKER_SERIALIZER_H
#define TALKER_SERIALIZER_H

#include <memory>
#include <actor_feature_serializer.h>

namespace amarlon {

class Talker;
typedef std::shared_ptr<Talker> TalkerPtr;

class TalkerSerializer : public ActorFeatureSerializer
{
public:
  TalkerSerializer();
  TalkerSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~TalkerSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // TALKER_SERIALIZER_H
