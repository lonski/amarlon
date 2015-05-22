#include "destroyable.h"
#include <stdlib.h>
#include <time.h>
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

DestroyablePtr Destroyable::create(DescriptionPtr dsc)
{
  DestroyablePtr destroyable(new Destroyable);

  DestroyableDescriptionPtr destrDsc = std::dynamic_pointer_cast<DestroyableDescription>( dsc );
  if ( destrDsc )
  {
    destroyable->_dropRules = destrDsc->dropRules;
  }

  return destroyable;
}

ActorFeaturePtr Destroyable::clone()
{
  DestroyablePtr cloned(new Destroyable);
  cloned->_dropRules = _dropRules;

  return cloned;
}

bool Destroyable::isEqual(ActorFeaturePtr rhs)
{
  bool equal = true;

  DestroyablePtr dRhs = std::dynamic_pointer_cast<Destroyable>(rhs);
  if ( dRhs )
  {
    equal = _dropRules.size() == dRhs->_dropRules.size() &&
            std::equal(_dropRules.begin(), _dropRules.end(), dRhs->_dropRules.begin());
  }

  return equal;
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
    processDropRules();
  }
}

float roll()
{
  srand( time(nullptr) );
  return ((rand() % 100) + 1) / 100.0f;
}

int roll(int from, int to)
{
  srand( time(nullptr) );
  return from + ( rand() % (to-from)+1 );
}

ActorPtr createActor(const DropRule& rule)
{
  ActorPtr toDrop = Actor::create(rule.dropActorId);
  PickablePtr pickable = toDrop->getFeature<Pickable>();
  if ( pickable )
  {
    pickable->setAmount( roll( rule.amountMin, rule.amountMax ) );
  }

  return toDrop;
}

void Destroyable::processDropRules()
{
  for( DropRule& rule : _dropRules )
  {
    if ( rule.chance > roll() )
    {
      ActorPtr toDrop = createActor(rule);
      dropOnGround( toDrop );
    }
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

