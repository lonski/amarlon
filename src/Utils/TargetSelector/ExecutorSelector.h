#ifndef EXECUTORSELECTOR_H
#define EXECUTORSELECTOR_H

#include "TargetSelector.h"

namespace amarlon {

class ExecutorSelector : public TargetSelector
{
public:
  ExecutorSelector();

  virtual std::vector<Actor*> select(Actor* executor, Map* map, bool (*filterFun)(Actor*) = nullptr);

};

}

#endif // EXECUTORSELECTOR_H
