#include "cmd_look.h"
#include <single_range_selector.h>
#include <engine.h>
#include <gui.h>
#include <messenger.h>
#include <actor.h>
#include <fixed_size_text_window.h>

namespace amarlon {

bool CmdLook::accept(TCOD_key_t &key)
{
    return key.vk == TCODK_CHAR && key.c == 'l';
}

int CmdLook::execute()
{
  SingleRangeSelector selector("Select a tile to inspect...");
  selector.setRange(5);
  Target target = selector.select();

  if (!target.actors.empty())
  {

    auto characterIter = std::find_if(target.actors.begin(), target.actors.end(), [](ActorPtr a){ return a->hasFeature<Character>();});
    if ( characterIter != target.actors.end() )
    {
      Engine::instance()
          .getWindowManager()
          .getWindow<gui::FixedSizeTextWindow>()
          .setText( (*characterIter)->getDescription() )
          .show();
    }
    else
    {
      auto objectIter = std::find_if(target.actors.begin(), target.actors.end(), [](ActorPtr a){ return !a->hasFeature<Character>() && !a->hasFeature<Pickable>();});
      if ( objectIter != target.actors.end() )
      {
        Messenger::message()->lookAtObject(*objectIter);
      }
      else
      {
        target.actors.erase(std::remove_if(target.actors.begin(), target.actors.end(), [](ActorPtr a){return !a->hasFeature<Pickable>();}), target.actors.end());
        if ( !target.actors.empty() )
        {
          Messenger::message()->lookAtSomeItems( target.actors.size() > 1 );
        }
      }
    }
  }
  return 1;
}


}
