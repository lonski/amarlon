#include "destroyable.h"
#include <container.h>
#include <map.h>
#include <actor.h>

namespace amarlon {

const ActorFeature::Type Destroyable::featureType = ActorFeature::DESTROYABLE;

Destroyable::Destroyable()
{
}

Destroyable::~Destroyable()
{
}

DestroyablePtr Destroyable::create(DescriptionPtr)
{
  return DestroyablePtr(new Destroyable);
}

ActorFeaturePtr Destroyable::clone()
{
  return DestroyablePtr(new Destroyable);
}

bool Destroyable::isEqual(ActorFeaturePtr)
{
  return true;
}

ActorFeature::Type Destroyable::getType()
{
  return Destroyable::featureType;
}

void Destroyable::destroy()
{
  ActorPtr owner = getOwner().lock();
  if ( owner )
  {
    dropInventory();
  }
}

void Destroyable::dropInventory()
{
  ActorPtr owner = getOwner().lock();
  if (owner)
  {
    ContainerPtr inventory = owner->getFeature<Container>();
    if ( inventory )
    {
      for ( ActorPtr item : inventory->content() )
      {
        inventory->remove(item);
        dropOnGround(item);
      }
    }
  }
}


void Destroyable::dropOnGround(ActorPtr item)
{
  ActorPtr owner = getOwner().lock();
  if (owner)
  {
    MapPtr map = owner->getMap();
    if ( map != nullptr )
    {
      item->setX( owner->getX() );
      item->setY( owner->getY() );
      map->addActor(item);
    }
  }
}

}

