#ifndef SINGLENEIGHBOURSELECTOR_H
#define SINGLENEIGHBOURSELECTOR_H

#include "target_selector.h"

namespace amarlon {

class SingleNeighbourSelector : public TargetSelector
{
public:
  SingleNeighbourSelector(const std::string& selectionMessage = "Select a tile..");

  virtual Target select(std::function<bool (amarlon::ActorPtr)> filterFun = [](ActorPtr){ return true;});
};

}

#endif // SINGLENEIGHBOURSELECTOR_H
