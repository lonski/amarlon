#include "TargetSelector.h"
#include "ExecutorSelector.h"
#include "SingleNeighbourSelector.h"

namespace amarlon {

TargetSelector::TargetSelector()
{
}

TargetSelector *TargetSelector::create(SelectorType type)
{
  TargetSelector* ts = nullptr;

  switch(type)
  {
    case SelectorType::Executor: ts = new ExecutorSelector; break;
    case SelectorType::SingleNeighbour: ts = new SingleNeighbourSelector; break;
    default:;
  }

  return ts;
}

}
