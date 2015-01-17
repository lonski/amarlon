#ifndef OPENABLEDOOR_H
#define OPENABLEDOOR_H

#include "openable.h"

namespace amarlon {

class OpenableDoor : public Openable
{
public:
  OpenableDoor();

  virtual ActorFeature* clone();
  virtual bool isEqual(ActorFeature *rhs);

  virtual bool open(Actor* executor);
  virtual bool close(Actor* executor);

  virtual bool lock();

};

}

#endif // OPENABLEDOOR_H
