#ifndef AI_H
#define AI_H

#include "actor_feature.h"
#include "ai_type.h"
#include "data_gateways/actor_descriptions.h"

namespace amarlon {

class Actor;
class Map;

class Ai : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Ai();
  virtual ~Ai() {}

  virtual ActorFeature::Type getType() { return featureType; }
  virtual void update(Map* map);

  static Ai* create(AiType type);
  static Ai* create(Description* dsc);

};

}

#endif // AI_H
