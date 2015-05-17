#ifndef OPENABLEDOOR_H
#define OPENABLEDOOR_H

#include <memory>
#include "openable.h"

namespace amarlon {

class OpenableDoor;
typedef std::shared_ptr<OpenableDoor> OpenableDoorPtr;

class OpenableDoor : public Openable
{
public:
  OpenableDoor();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);

  virtual bool open(ActorPtr executor);
  virtual bool close(ActorPtr executor);

  virtual bool lock();

};

}

#endif // OPENABLEDOOR_H
