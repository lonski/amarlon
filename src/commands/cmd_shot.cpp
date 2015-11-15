#include "cmd_shot.h"
#include <single_range_projectile_selector.h>
#include <engine.h>
#include <actor.h>
#include <shot_action.h>

namespace amarlon {

CmdShot::CmdShot()
{
}

bool CmdShot::accept(const TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 't' );
}

int CmdShot::execute()
{
  int turns = 0;

  ActorPtr player = Engine::instance().getPlayer();

  if ( WearerPtr wearer = player->getFeature<Wearer>() )
  {
    if ( ActorPtr weaponActor = wearer->equipped( ItemSlotType::MainHand ) )
    {
      if ( PickablePtr weapon = weaponActor->getFeature<Pickable>() )
      {
        SingleRangeProjectileSelector selector("Press [TAB] to change target. Press [ESC] to cancel.");
        selector.setRange( weapon->getRange() * 2 );
        selector.setRadius( weapon->getRange() * 2 );
        Target target = selector.select();
        if ( !target.actors.empty() )
        {
          player->performAction( new ShotAction( target.firstActor()) );
          ++turns;
        }
      }
    }
  }

  return turns;
}

}
