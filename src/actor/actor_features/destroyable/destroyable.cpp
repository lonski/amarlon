#include "destroyable.h"
#include <dices.h>
#include <inventory.h>
#include <map.h>
#include <actor.h>
#include <actor_descriptions.h>

namespace amarlon {

const ActorFeature::Type Destroyable::featureType = ActorFeature::DESTROYABLE;

Destroyable::Destroyable(DescriptionPtr dsc)
{
  upgrade(dsc);
}

Destroyable::~Destroyable()
{
}

DestroyablePtr Destroyable::create(DescriptionPtr dsc)
{
  return DestroyablePtr( new Destroyable(dsc) );
}

void Destroyable::upgrade(DescriptionPtr dsc)
{
  DestroyableDescriptionPtr destrDsc = std::dynamic_pointer_cast<DestroyableDescription>( dsc );
  if ( destrDsc )
  {
    _dropRules.insert(_dropRules.end(), destrDsc->dropRules.begin(), destrDsc->dropRules.end());
  }
}

DescriptionPtr Destroyable::toDescriptionStruct(ActorFeaturePtr)
{
  DestroyableDescriptionPtr dsc(new DestroyableDescription);

  dsc->dropRules = _dropRules;

  return dsc;
}

ActorFeaturePtr Destroyable::clone()
{
  DestroyablePtr cloned(new Destroyable);
  cloned->_dropRules = _dropRules;

  return cloned;
}

bool Destroyable::isEqual(ActorFeaturePtr rhs) const
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

const std::vector<DropRule> Destroyable::getDropRules() const
{
  return _dropRules;
}

ActorPtr createActor(const DropRule& rule)
{
  ActorPtr toDrop = Actor::create(rule.dropActorId);
  PickablePtr pickable = toDrop->getFeature<Pickable>();
  if ( pickable )
  {
    pickable->setAmount( dices::roll( rule.amountMin, rule.amountMax ) );
  }

  return toDrop;
}

void Destroyable::processDropRules()
{
  for( DropRule& rule : _dropRules )
  {
    if ( rule.chance > (dices::roll(dices::D100) / 100.0f) )
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
    InventoryPtr inventory = owner->getFeature<Inventory>();
    if ( inventory )
    {
      for ( ActorPtr item : inventory->items() )
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
      item->setMap(nullptr);
      item->setPosition( owner->getX(), owner->getY() );
      map->addActor(item);
    }
  }
}

}

