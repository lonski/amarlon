#include "target_selector.h"
#include "executor_selector.h"
#include "single_neighbour_selector.h"

namespace amarlon {

TargetSelector::TargetSelector(const std::string &selectionMessage)
  : _selectionMessage(selectionMessage)
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

TargetSelector& TargetSelector::setUpdateFunction(std::function<void ()> fun)
{
  _updateFunction = fun;
  return *this;
}

TargetSelector &TargetSelector::setSelectionMessage(const std::string &msg)
{
  _selectionMessage = msg;
  return *this;
}

}
