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

void CmdLook::execute()
{
  SingleRangeSelector selector(50,"Select a tile to inspect...");
  std::vector<ActorPtr> actors = selector.select();

  if (!actors.empty())
  {

    auto characterIter = std::find_if(actors.begin(), actors.end(), [](ActorPtr a){ return a->hasFeature<Character>();});
    if ( characterIter != actors.end() )
    {
      Engine::instance()
          .windowManager()
          .getWindow<gui::FixedSizeTextWindow>()
          .setText( (*characterIter)->getDescription() )
          .show();
    }
    else
    {
      auto objectIter = std::find_if(actors.begin(), actors.end(), [](ActorPtr a){ return !a->hasFeature<Character>() && !a->hasFeature<Pickable>();});
      if ( objectIter != actors.end() )
      {
        Messenger::message()->lookAtObject(*objectIter);
      }
      else
      {
        actors.erase(std::remove_if(actors.begin(), actors.end(), [](ActorPtr a){return !a->hasFeature<Pickable>();}), actors.end());
        if ( !actors.empty() )
        {
          Messenger::message()->lookAtSomeItems( actors.size() > 1 );
        }
      }
    }
  }

}


}
