#include "pickable.h"
#include "Actor/actor.h"

Pickable::Pickable()
{
}

bool Pickable::pick(Actor *owner, Actor *picker)
{
  bool r = false;

  if ( picker->afContainer )
  {
    r = picker->afContainer->add(owner);
  }

  return r;
}

Actor *Pickable::drop(Actor *owner)
{
  //in future for example block when cursed item
  return owner;
}

void Pickable::use(Actor *owner, Actor *user)
{

}
