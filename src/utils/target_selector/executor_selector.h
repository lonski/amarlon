#ifndef EXECUTORSELECTOR_H
#define EXECUTORSELECTOR_H

#include "target_selector.h"

namespace amarlon {

class ExecutorSelector : public TargetSelector
{
public:
  ExecutorSelector();

  virtual Target select(std::function<bool (amarlon::ActorPtr)> filterFun = [](ActorPtr){return true;});

};

}

#endif // EXECUTORSELECTOR_H
