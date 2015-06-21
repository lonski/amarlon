#include "openable_container.h"
#include "actor/actor.h"
#include "engine.h"
#include "utils/messenger.h"
#include "utils/utils.h"
#include "gui/window/pick_up_window.h"
#include "gui/message_box.h"

namespace amarlon {

OpenableContainer::OpenableContainer()
{
}

bool OpenableContainer::open(ActorPtr executor)
{
  bool r = false;

  if ( getOwner().lock()->hasFeature<Container>() )
  {
    auto afterPickupAction =
    [&](const std::string& item, int amount)
    {
      Messenger::message()->actorPicked(executor->getName(), item, amount, getOwner().lock()->getName());
    };

    auto inventoryFullAction =
    [&](const std::string& item)
    {
      gui::msgBox("Cannot pickup "+item+" from "+tolowers(getOwner().lock()->getName())+":\nInventory is full!",
                  gui::MsgType::Error);
    };

    Engine::instance().windowManager()
                      .getWindow<gui::PickUpWindow>()
                      .setPicker(executor)
                      .setContainer(getOwner().lock()->getFeature<Container>())
                      .setFilterFunction( [](ActorPtr a){ return a && a->getFeature<Pickable>() != nullptr; } )
                      .setAfterPickupAction( afterPickupAction )
                      .setInventoryFullAction( inventoryFullAction )
                      .show();

    r = true;
  }

  return r;
}

bool OpenableContainer::close(ActorPtr)
{
  return true;
}

ActorFeaturePtr OpenableContainer::clone()
{
  OpenableContainerPtr cloned( new OpenableContainer );
  cloned->setLockId( getLockId() );
  isLocked() ? cloned->lock() : cloned->unlock();

  return cloned;
}

bool OpenableContainer::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  OpenableContainerPtr crhs = std::dynamic_pointer_cast<OpenableContainer>(rhs);

  if (crhs)
  {
    equal = (_lockId == crhs->_lockId);
  }

  return equal;
}

OpenablePtr OpenableContainer::Creator::create(OpenableDescriptionPtr dsc)
{
  OpenablePtr op = nullptr;

  OpenableContainerDescriptionPtr contDsc = std::dynamic_pointer_cast<OpenableContainerDescription>(dsc);
  if ( contDsc != nullptr )
  {
    op = std::make_shared<OpenableContainer>();
    Openable::Creator::fillCommonOpenablePart(op, dsc);
  }

  return op;
}

}
