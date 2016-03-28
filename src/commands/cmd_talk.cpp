#include "cmd_talk.h"
#include <single_neighbour_selector.h>
#include <talker.h>
#include <engine.h>
#include <actor.h>
#include <dialog.h>
#include <engine.h>
#include <window_manager.h>
#include <talk_window.h>

namespace amarlon {

CmdTalk::CmdTalk()
{
}

bool CmdTalk::accept(const TCOD_key_t& key)
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

    Engine::instance().render();
    TCODConsole::root->flush();
  }

  return turns;
}

std::pair<Dialog, Choice> CmdTalk::display(const Dialog &d)
{
  if ( d.id > 0 )
  {
    auto& window = Engine::instance()
                 .getWindowManager()
                 .getWindow<gui::TalkWindow>();

    window.setDialog(d);
    window.show();

    return std::make_pair( d, window.getChoice() );
  }
  return std::make_pair( d, Choice() );
}

}
