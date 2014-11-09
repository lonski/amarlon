#ifndef TARGETSELECTOR_H
#define TARGETSELECTOR_H

#include <vector>
#include "utils/selector_type.h"

namespace amarlon {

class Actor;
class Map;

class TargetSelector
{
public:
  TargetSelector();
  virtual ~TargetSelector() {}

  static TargetSelector* create(SelectorType type);

  virtual std::vector<Actor*> select(Actor* executor, Map* map, bool (*filterFun)(Actor*) = nullptr) = 0;

};

}

#endif // TARGETSELECTOR_H
