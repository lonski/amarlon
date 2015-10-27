#include "transcribe_action.h"
#include <scroll.h>
#include <inventory.h>
#include <actor.h>

namespace amarlon {

TranscribeAction::TranscribeAction(ScrollPtr scroll)
  : _scroll(scroll)
{
}

TranscribeAction::~TranscribeAction()
{
}

bool TranscribeAction::perform(ActorPtr performer)
{
  bool transcribed = false;
  _performer = performer;

  if ( _scroll != nullptr )
  {
    transcribed = _scroll->transcribe(_performer);
    if ( _scroll->getUsesCount() == 0 )
    {
      removeTranscribedScrollFromInventory();
    }
  }

  return transcribed;
}

ActorActionUPtr TranscribeAction::clone()
{
  TranscribeActionUPtr cloned = std::make_unique<TranscribeAction>(_scroll);
  cloned->_performer = _performer;

  return std::move(cloned);
}

void TranscribeAction::removeTranscribedScrollFromInventory()
{
  InventoryPtr container = _performer->getFeature<Inventory>();

  if ( _scroll && container )
  {
    ActorPtr toRemove = _scroll->spilt(1);
    container->remove( toRemove );
  }
}

}
