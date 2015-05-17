#ifndef EXECUTORSELECTOR_H
#define EXECUTORSELECTOR_H

#include "target_selector.h"

namespace amarlon {

class ExecutorSelector : public TargetSelector
{
public:
  ExecutorSelector();

  virtual std::vector<ActorPtr> select(std::function<bool (amarlon::ActorPtr)>* filterFun = nullptr);

};

}

#endif // EXECUTORSELECTOR_H
