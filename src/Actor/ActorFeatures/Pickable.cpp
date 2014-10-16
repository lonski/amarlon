#include "Pickable.h"
#include "Actor/Actor.h"

Pickable::Pickable()
{
}

bool Pickable::pick(Actor *picker)
{
  bool r = false;

  if ( picker->afContainer() && _owner )
  {
    r = picker->afContainer()->add(_owner);
  }

  return r;
}

Actor *Pickable::drop()
{
  //in future for example block when cursed item
  return _owner;
}

void Pickable::use(Actor*)
{

}
