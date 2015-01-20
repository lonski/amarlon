#ifndef SINGLENEIGHBOURSELECTOR_H
#define SINGLENEIGHBOURSELECTOR_H

#include "target_selector.h"

namespace amarlon {

class SingleNeighbourSelector : public TargetSelector
{
public:
  SingleNeighbourSelector(const std::string& selectionMessage = "Select a tile..");

  virtual std::vector<Actor*> select(std::function<bool (amarlon::Actor*)>* filterFun = nullptr);
  virtual Actor* selectFirst(std::function<bool (amarlon::Actor*)>* filterFun = nullptr);
};

}

#endif // SINGLENEIGHBOURSELECTOR_H
