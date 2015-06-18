#ifndef AI_H
#define AI_H

#include <memory>
#include "actor_feature.h"
#include "ai_type.h"
#include "data_gateways/actor_descriptions.h"

namespace amarlon {

class Actor;
class Map;
class Ai;

typedef std::shared_ptr<Ai> AiPtr;
typedef std::shared_ptr<Map> MapPtr;

class Ai : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Ai();
  virtual ~Ai() {}

  virtual ActorFeature::Type getType() { return featureType; }
  virtual void update() = 0;

  static AiPtr create(AiType type);
  static AiPtr create(DescriptionPtr dsc);

};

}

#endif // AI_H
