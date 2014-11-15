#ifndef AI_H
#define AI_H

#include "ActorFeature.h"
#include "AiType.h"
#include "DataGateways/ActorDescriptions.h"

namespace amarlon {

class Actor;
class Map;

class Ai : public ActorFeature
{
public:
  Ai();
  virtual ~Ai() {}

  static FeatureType getType() { return ActorFeature::AI; }
  virtual void update(Map* map);

  static Ai* create(AiType type);
  static Ai* create(Description* dsc);

};

}

#endif // AI_H
