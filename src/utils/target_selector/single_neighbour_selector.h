#ifndef SINGLENEIGHBOURSELECTOR_H
#define SINGLENEIGHBOURSELECTOR_H

#include "target_selector.h"

namespace amarlon {

class SingleNeighbourSelector : public TargetSelector
{
public:
  SingleNeighbourSelector(const std::string& selectionMessage = "Select a tile..");

  virtual std::vector<ActorPtr> select(std::function<bool (amarlon::ActorPtr)>* filterFun = nullptr);
  virtual ActorPtr selectFirst(std::function<bool (amarlon::ActorPtr)>* filterFun = nullptr);
};

}

#endif // SINGLENEIGHBOURSELECTOR_H
