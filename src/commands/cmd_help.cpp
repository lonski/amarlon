#include "cmd_help.h"
#include <sstream>
#include <iomanip>
#include <resizeable_text_window.h>
#include <engine.h>
#include <actor.h>
#include <playable_character.h>

namespace amarlon {

CmdHelp::CmdHelp()
{
}

bool CmdHelp::accept(TCOD_key_t &key)
{
  return key.vk == TCODK_CHAR && key.c == '?';
}

int CmdHelp::execute()
{
  /*
   * displaying ASCII codes mapped characters
   * in future here will be in game manual
   */

  std::stringstream ss;
  for(int c=0; c < 255; ++c)
  {
    ss << "[" << static_cast<char>(c)
       << " "
       << std::setw(3) << c << "]";

    if ( c % 10 == 0) ss << "\n";
  }

//  Engine::instance().getWindowManager()
//                    .getWindow<gui::ResizeableTextWindow>()
//                    .setCenterGameScreen()
//                    .setWindowTitle("Help")
//                    .setWindowText( ss.str() )
//                    .show();

  auto player = Engine::instance().getPlayer();
  PlayableCharacterPtr c = player->getFeature<PlayableCharacter>();
  c->advanceLevel();

  return 0;
}

}

