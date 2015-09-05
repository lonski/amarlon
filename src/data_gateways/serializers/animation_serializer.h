#ifndef ANIMATION_SERIALIZER_H
#define ANIMATION_SERIALIZER_H

#include <memory>
#include <serializer.h>

namespace amarlon {

namespace animation {
  class Animation;
  typedef std::shared_ptr<Animation> AnimationPtr;
}

class AnimationSerializer : public Serializer
{
public:
  AnimationSerializer();
  AnimationSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~AnimationSerializer();

  virtual bool serialize(animation::AnimationPtr anim);

};

}

#endif // ANIMATION_SERIALIZER_H
