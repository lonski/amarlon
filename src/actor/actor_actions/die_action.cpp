#include "die_action.h"
#include <actor.h>
#include <map.h>

namespace amarlon
{

DieAction::DieAction()
{
}

DieAction::~DieAction()
{
}

ActorActionUPtr DieAction::clone()
{
  auto cloned = std::make_unique<DieAction>();
  cloned->_performer = _performer;

  return std::move(cloned);
}

bool DieAction::perform(ActorPtr performer)
{
  _performer = performer;

  if (_performer)
  {
    dropItemsFromBody();

    DestroyablePtr destroyable = _performer->getFeature<Destroyable>();
    if ( destroyable )
    {
      destroyable->destroy();
    }

    _performer->morph(ActorType::Corpse);
  }

  return _performer != nullptr;
}

void DieAction::dropItemsFromBody()
{
  WearerPtr wearer = _performer->getFeature<Wearer>();
  if ( wearer )
  {
    for ( auto slot : ItemSlotType() )
    {
      ActorPtr item = wearer->unequip(slot);
      if ( item )
      {
        dropOnGround( item );
      }
    }
  }
}

void DieAction::dropOnGround(ActorPtr item)
{
  MapPtr map = _performer->getMap();
  if ( map != nullptr )
  {
    item->setPosition( _performer->getX(), _performer->getY() );
    map->addActor(item);
  }
}

}
