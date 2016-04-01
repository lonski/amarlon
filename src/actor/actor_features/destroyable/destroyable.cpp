#include "destroyable.h"
#include <dices.h>
#include <inventory.h>
#include <map.h>
#include <actor.h>



namespace amarlon {

const ActorFeature::Type Destroyable::FeatureType = ActorFeature::DESTROYABLE;

DestroyablePtr Destroyable::create(const DestroyableData &data)
{
  return DestroyablePtr( new Destroyable(data) );
}

Destroyable::Destroyable()
{
}

Destroyable::Destroyable(const Destroyable &rhs)
{
  *this = rhs;
}

Destroyable::~Destroyable()
{
}

bool Destroyable::operator==(const Destroyable& rhs) const
{
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

Destroyable &Destroyable::operator=(const Destroyable& rhs)
{
  if ( this != &rhs )
  {
    _data.CopyFrom(rhs._data);
  }
  return *this;
}

const DestroyableData &Destroyable::getData() const
{
  return _data;
}

const google::protobuf::Message& Destroyable::getDataPolymorphic() const
{
  return getData();
}

Destroyable::Destroyable(const DestroyableData &data)
{
  _data.CopyFrom(data);
}

ActorFeature::Type Destroyable::getFeatureType()
{
  return Destroyable::FeatureType;
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

ActorPtr createActor(const DropRule& rule)
{
  ActorPtr toDrop = Actor::create( static_cast<ActorType>(rule.actor_id()) );
  PickablePtr pickable = toDrop->getFeature<Pickable>();
  if ( pickable )
  {
    pickable->setAmount( dices::roll( rule.min(), rule.max() ) );
  }

  return toDrop;
}

void Destroyable::processDropRules()
{
  for( auto it = _data.droprules().begin(); it != _data.droprules().end(); ++it )
  {
    const DropRule& rule = *it;
    if ( rule.chance() > (dices::roll(dices::D100) / 100.0f) )
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
      item->setPosition( owner->getX(), owner->getY() );
      map->addActor(item);
    }
  }
}

}

