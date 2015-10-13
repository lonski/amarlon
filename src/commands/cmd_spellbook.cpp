#include "cmd_spellbook.h"
#include <engine.h>
#include <world.h>
#include <window_manager.h>
#include <spellbook_window.h>
#include <actor.h>

namespace amarlon {

CmdSpellbook::CmdSpellbook()
{
}

bool CmdSpellbook::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'S' );
}

int CmdSpellbook::execute()
{
  ActorPtr player = Engine::instance().getWorld().getPlayer();
  CharacterPtr character = player->getFeature<Character>();
  if ( character )
    {
    SpellBookPtr spellbook = character->getSpellBook();
    if ( spellbook )
    {
      Engine::instance().getWindowManager()
                        .getWindow<gui::SpellBookWindow>()
                        .setSpellBook(spellbook)
                        .show();
    }
  }

  return 0;
}

}
