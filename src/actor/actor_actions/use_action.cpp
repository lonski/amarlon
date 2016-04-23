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

ActorActionResult UseAction::perform(ActorPtr performer)
{
  ActorActionResult r = ActorActionResult::Nok;
  _performer = performer;

  PickablePtr p = _toUse->getFeature<Pickable>();
  if ( p != nullptr && p->use( _performer, _target ) )
  {
    if ( p->getUsesCount() == 0 && p->getUseType() == UseType::FixedUses )
    {
      removeUsedItemFromInventory();
    }

    r = ActorActionResult::Ok;
  }

  return r;
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

