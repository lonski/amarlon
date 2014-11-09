#include "CmdHelp.h"
#include <Gui/Window/text_window.h>
#include <Engine.h>
#include <sstream>
#include <iomanip>

namespace amarlon {

CmdHelp::CmdHelp()
{
}

bool CmdHelp::accept(TCOD_key_t &key)
{
  return key.vk == TCODK_CHAR && key.c == '?';
}

void CmdHelp::execute(Actor *)
{
  std::stringstream ss;
  for(int c=0; c < 255; ++c)
  {
    ss << "[" << static_cast<char>(c)
       << " "
       << std::setw(3) << c << "]";

    if ( c % 10 == 0) ss << "\n";
  }

  Engine::instance().windowManager()
                    .getWindow<gui::TextWindow>()
                    .setCenterGameScreen()
                    .setWindowTitle("Help")
                    .setWindowText( ss.str() )
                    .show();

}

}
