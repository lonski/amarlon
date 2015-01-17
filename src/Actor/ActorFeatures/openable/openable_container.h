#ifndef OPENABLECONTAINER_H
#define OPENABLECONTAINER_H

#include "openable.h"

namespace amarlon {

class OpenableContainer : public Openable
{
public:
  OpenableContainer();

  virtual ActorFeature* clone();
  virtual bool isEqual(ActorFeature *rhs);

  virtual bool open(Actor* executor);
  virtual bool close(Actor* executor);

};

}

#endif // OPENABLECONTAINER_H
