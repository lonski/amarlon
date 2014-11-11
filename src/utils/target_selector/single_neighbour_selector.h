#ifndef SINGLENEIGHBOURSELECTOR_H
#define SINGLENEIGHBOURSELECTOR_H

#include "target_selector.h"

namespace amarlon {

class SingleNeighbourSelector : public TargetSelector
{
public:
  SingleNeighbourSelector();

  virtual std::vector<Actor*> select(Actor* executor, Map* map, bool (*filterFun)(Actor*) = nullptr);
  virtual Actor* selectFirst(Actor* executor, Map* map, bool (*filterFun)(Actor*) = nullptr);
};

}

#endif // SINGLENEIGHBOURSELECTOR_H
