#ifndef EXECUTORSELECTOR_H
#define EXECUTORSELECTOR_H

#include "target_selector.h"

namespace amarlon {

class ExecutorSelector : public TargetSelector
{
public:
  ExecutorSelector();

  virtual std::vector<Actor*> select(std::function<bool (amarlon::Actor*)>* filterFun = nullptr);

};

}

#endif // EXECUTORSELECTOR_H
