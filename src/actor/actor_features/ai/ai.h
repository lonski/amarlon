#ifndef AI_H
#define AI_H

#include <memory>
#include <actor_feature.h>
#include <actor_descriptions.h>

namespace amarlon {

class Ai;
typedef std::shared_ptr<Ai> AiPtr;

class Ai : public ActorFeature
{
public:

  class Creator
  {
  public:
    virtual ~Creator() {}
    virtual AiPtr create(AiDescriptionPtr dsc) = 0;
  };

  const static ActorFeature::Type featureType;

  Ai();
  virtual ~Ai() {}

  virtual ActorFeature::Type getType() { return featureType; }
  virtual void update() = 0;

  static AiPtr create(DescriptionPtr dsc);

};

}

#endif // AI_H
