#include "cmd_move.h"
#include <utils.h>
#include <map.h>
#include <move_action.h>
#include <attack_action.h>
#include <talker.h>
#include <engine.h>
#include <window_manager.h>
#include <menu_window.h>
#include <alabel_menu_item.h>
#include <message_box.h>
#include <character.h>

namespace amarlon {

CmdMove::CmdMove()
  : _dx(0)
  , _dy(0)
{
}

bool CmdMove::accept(const TCOD_key_t& key)
{
  _dx = 0;
  _dy = 0;
  return handleDirectionKey(key, _dx, _dy);
}

int CmdMove::execute()
{
  ActorPtr player = Engine::instance().getPlayer();

  //if MoveAction failed then path is blocked
  if ( player && player->performAction( new MoveAction(_dx, _dy) ) != ActorActionResult::Ok )
  {
    ActorPtr actor = getActorOnPath();
    if ( actor && actor != player )
    {
      //attack hostile actor
      if ( actor->isHostileTo(player) )
      {
        player->performAction( new AttackAction(actor) );
      }
      //ask to attack non hostile actor
      else if ( gui::questionBox("Are you sure you want to attack "+actor->getName()+"?",
                                 gui::MsgType::Info) == gui::QuestionDialog::Response::YES )
      {
        actor->getFeature<Character>()->turnHostileTo(player);
        player->performAction( new AttackAction(actor) );
      }
    }
  }
  return 1;
}

ActorPtr CmdMove::getActorOnPath()
{
  ActorPtr actor;
  MapPtr map = Engine::instance().getPlayer()->getMap();

  if ( map )
  {
    int targetX = Engine::instance().getPlayer()->getX() + _dx;
    int targetY = Engine::instance().getPlayer()->getY() + _dy;

    std::function<bool (amarlon::ActorPtr)> filterFun = [&](amarlon::ActorPtr a)->bool
    {
      return a->hasFeature<Character>() && a->getFeature<Character>()->isAlive();
    };

    auto targets = map->getActors(targetX, targetY, filterFun);
    if ( !targets.empty() )
    {
      actor = targets.front();
    }
  }

  return actor;
}

void CmdMove::setDirection(int dx, int dy)
{
  if (dx > 0) _dx = 1;
  else if (dx < 0) _dx = -1;

  if (dy > 0) _dy = 1;
  else if (dy < 0) _dy = -1;
}

}

