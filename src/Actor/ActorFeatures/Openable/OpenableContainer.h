#ifndef OPENABLECONTAINER_H
#define OPENABLECONTAINER_H

#include "Openable.h"

class OpenableContainer : public Openable
{
public:
  OpenableContainer();

  virtual bool open(Actor* executor);
  virtual bool close(Actor* executor);
  virtual ActorFeature* clone();

};

#endif // OPENABLECONTAINER_H
