#include "cmd_rest.h"
#include <actor.h>
#include <character.h>
#include <world.h>
#include <map.h>
#include <engine.h>
#include <message_box.h>

namespace amarlon {

static const int TURNS_PER_HOUR = 60/5;

CmdRest::CmdRest()
  : _restHours(8)
{
}

bool CmdRest::accept(const TCOD_key_t& key)
{
  return key.vk == TCODK_CHAR && key.c == 'R';
}

int CmdRest::execute()
{
  MapPtr map = Engine::instance().getWorld().getCurrentMap();
  ActorPtr player = Engine::instance().getPlayer();

  auto mobs = map->getActors([&](ActorPtr a){
                auto mob = a->getFeature<Ai>();
                ActorPtr target = mob ? mob->getTarget().firstActor() : nullptr;
                return mob && target == player && mob->isHunting();
              });

  if ( !mobs.empty() )
  {
    gui::msgBox("Can not rest when there are monsters nearby!", gui::MsgType::Warning);
  }
  else
  {
    fadeIn();
    tickTime();
    restoreCharacters();
    Engine::instance().render();
    Engine::instance().flush();
    fadeOut();

    gui::msgBox("You rested for "+toStr(_restHours)+" hours.", gui::MsgType::Info);
  }

  return 0;
}

void CmdRest::tickTime()
{
  for ( int t=0; t<(_restHours * TURNS_PER_HOUR); ++t ) Engine::instance().update();
}

void CmdRest::restoreCharacters()
{
  MapPtr map = Engine::instance().getWorld().getCurrentMap();
  for ( auto actor : map->getActors() )
  {
    actor->tickDay();
  }
}

void CmdRest::fadeIn()
{
  for (int fade=255; fade >= 0; --fade)
  {
      TCODConsole::setFade(fade,TCODColor::black);
      TCODConsole::flush();
  }
}

void CmdRest::fadeOut()
{
  for (int fade=0; fade <= 255; ++fade)
  {
      TCODConsole::setFade(fade,TCODColor::black);
      TCODConsole::flush();
  }
}

}
