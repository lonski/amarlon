#include "cmd_talk.h"
#include <single_neighbour_selector.h>
#include <talker.h>
#include <engine.h>
#include <actor.h>
#include <dialog.h>

namespace amarlon {

CmdTalk::CmdTalk()
{
}

bool CmdTalk::accept(TCOD_key_t &key)
{
  return key.vk == TCODK_CHAR && key.c == 'T';
}

int CmdTalk::execute()
{
  int turns = 0;

  SingleNeighbourSelector selector("Choose who to talk to..");
  Target target = selector.select([](ActorPtr a){ return a && a->hasFeature<Talker>(); });

  if ( !target.actors.empty() )
  {
    ActorPtr player = Engine::instance().getPlayer();
    TalkerPtr talker = target.firstActor()->getFeature<Talker>();

    std::pair<Dialog, Choice> talk;
    do
    {
      talk = display( talker->talk( player,
                                    talk.first,
                                    talk.second ) );
    }
    while( talk.first.id != -1 );

  }

  return turns;
}

std::pair<Dialog, Choice> CmdTalk::display(const Dialog &d)
{
  //TODO: show window to player and allow answer choosing
  return std::make_pair(d, Choice() );
}

}
