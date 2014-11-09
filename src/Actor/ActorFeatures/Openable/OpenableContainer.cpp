#include "OpenableContainer.h"
#include <Gui/Window/pick_up_window.h>
#include <Actor/Actor.h>
#include <Engine.h>

namespace amarlon {

OpenableContainer::OpenableContainer()
{
}

bool OpenableContainer::open(Actor *executor)
{
  bool r = false;

  if ( _owner->afContainer() )
  {
    Engine::instance().windowManager()
                      .getWindow<gui::PickUpWindow>()
                      .setPicker(executor)
                      .setContainer(_owner->afContainer())
                      .setFilterFunction( [](Actor* a){ return a->afPickable();} )
                      .show();

    r = true;
  }

  return r;
}

bool OpenableContainer::close(Actor*)
{
  return true;
}

ActorFeature *OpenableContainer::clone()
{
  OpenableContainer* cloned = new OpenableContainer;
  cloned->setLockId( getLockId() );
  cloned->setLocked( isLocked() );

  return cloned;
}

bool OpenableContainer::isEqual(ActorFeature *rhs)
{
  bool equal = false;
  OpenableContainer* crhs = dynamic_cast<OpenableContainer*>(rhs);

  if (crhs)
  {
    equal = (_lockId == crhs->_lockId);
  }

  return equal;
}

}
