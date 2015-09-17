#include "openable_container.h"
#include <actor.h>
#include <engine.h>

#include <utils.h>
#include <pick_up_window.h>
#include <message_box.h>
#include <inventory.h>
#include <actor_descriptions.h>

namespace amarlon {

OpenableContainer::OpenableContainer()
{
}

bool OpenableContainer::open(ActorPtr executor)
{
  bool r = false;

  if ( getOwner().lock()->hasFeature<Inventory>() )
  {
    auto inventoryFullAction =
    [&](const std::string& item)
    {
      gui::msgBox("Cannot pickup "+item+" from "+tolowers(getOwner().lock()->getName())+":\nInventory is full!",
                  gui::MsgType::Error);
    };

    auto sourceFun = [&](){ return getOwner().lock()->getFeature<Inventory>()->items
                      (
                        [](ActorPtr a)->bool{ return a && a->getFeature<Pickable>() != nullptr; }
                      ); };

    Engine::instance().getWindowManager()
                      .getWindow<gui::PickUpWindow>()
                      .setPicker(executor)
                      .setSource( sourceFun )
                      .setRemoveAction( [&](ActorPtr a){ getOwner().lock()->getFeature<Inventory>()->remove(a); } )
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
  OpenableInventoryPtr cloned( new OpenableContainer );
  cloned->setLockId( getLockId() );
  isLocked() ? cloned->lock() : cloned->unlock();

  return cloned;
}

bool OpenableContainer::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  OpenableInventoryPtr crhs = std::dynamic_pointer_cast<OpenableContainer>(rhs);

  if (crhs)
  {
    equal = (_lockId == crhs->_lockId);
  }

  return equal;
}

OpenablePtr OpenableContainer::Creator::create(OpenableDescriptionPtr dsc)
{
  OpenablePtr op = nullptr;

  OpenableContaineryDescriptionPtr contDsc = std::dynamic_pointer_cast<OpenableContaineryDescription>(dsc);
  if ( contDsc != nullptr )
  {
    op = std::make_shared<OpenableContainer>();
    Openable::Creator::fillCommonOpenablePart(op, dsc);
  }

  return op;
}

}
