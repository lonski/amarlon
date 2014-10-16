#ifndef PICKABLE_H
#define PICKABLE_H

#include "ActorFeature.h"

class Actor;

class Pickable : public ActorFeature
{
public:
  Pickable();
  virtual ~Pickable() {}

  virtual bool pick(Actor* picker);
  virtual Actor* drop();
  virtual void use(Actor* user);

};

#endif // PICKABLE_H
