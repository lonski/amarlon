#ifndef SINGLENEIGHBOURSELECTOR_H
#define SINGLENEIGHBOURSELECTOR_H

#include "TargetSelector.h"

class SingleNeighbourSelector : public TargetSelector
{
public:
  SingleNeighbourSelector();

  virtual std::vector<Actor*> select(Actor* executor, Map* map, bool (*filterFun)(Actor*) = nullptr);
};

#endif // SINGLENEIGHBOURSELECTOR_H
