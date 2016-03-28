#ifndef SINGLENEIGHBOURSELECTOR_H
#define SINGLENEIGHBOURSELECTOR_H

#include <memory>
#include "target_selector.h"

namespace amarlon {

class DirectionSelector;
typedef std::shared_ptr<DirectionSelector> DirectionSelectorPtr;

class SingleNeighbourSelector : public TargetSelector
{
public:
  SingleNeighbourSelector(const std::string& selectionMessage = "Select a tile..");

  virtual Target select(std::function<bool (amarlon::ActorPtr)> filterFun = [](ActorPtr){ return true;});

protected:
  DirectionSelectorPtr _selector;

};

}

#endif // SINGLENEIGHBOURSELECTOR_H
