#include "use_action.h"
#include <actor.h>

namespace amarlon {

UseAction::UseAction(const Target& target, ActorPtr toUse)
  : _target(target)
  , _toUse(toUse)
{
}

UseAction::~UseAction()
{
}

bool UseAction::perform(ActorPtr performer)
{
  bool used = false;
  _performer = performer;

  PickablePtr pickable = _toUse->getFeature<Pickable>();
  if ( pickable != nullptr && pickable->use( _performer, _target ) )
  {
    if ( pickable->getUsesCount() == 0 )
    {
      removeUsedItemFromInventory();
    }

    used = true;
  }

  return used;
}

void UseAction::removeUsedItemFromInventory()
{
  PickablePtr pickable = _toUse->getFeature<Pickable>();
  InventoryPtr container = _performer->getFeature<Inventory>();

  if ( pickable && container )
  {
    ActorPtr toRemove = pickable->spilt(1);
    container->remove( toRemove );
  }
}

ActorActionUPtr UseAction::clone()
{
  UseActionUPtr cloned = std::make_unique<UseAction>(_target, _toUse);
  cloned->_performer = _performer;

  return std::move(cloned);
}

}
