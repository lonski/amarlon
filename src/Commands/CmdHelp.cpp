#include "CmdHelp.h"
#include <Gui/Window/text_window.h>
#include <Engine.h>

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
  Engine::instance().windowManager()
                    .getWindow<gui::TextWindow>()
                    .setCenterGameScreen()
                    .setWindowTitle("Help")
                    .setWindowText(
                                    "Move\n"
                                    "Key: Keypad numbers 1-9 or arrows\n\n"

                                    "Use\n"
                                    "Key: 'u'\n"
                                    "Result: Opens inventory window to choose item to use.\n \n"

                                    "Open\n"
                                    "Key: 'o'\n"
                                    "Possible targets: Doors, openable actors with inventory\n"
                                    "Usage: hit command key, and then choose direction using numpad or arrows.\n"
                                    "Result: opens door or displays container content of oppened actor\n \n"

                                    "Close\n"
                                    "Key: 'c'\n"
                                    "Possible targets: Doors\n"
                                    "Usage: hit command key, and then choose direction using numpad or arrows.\n"
                                    "Result: closes doors\n \n"

                                    "Pick\n"
                                    "Key: ','\n"
                                    "Possible targets: pickable actor\n"
                                    "Usage: hit command key while standing on actor/s\n \n"

                                    "Inventory\n"
                                    "Key: 'i'\n"
                                    "Result: displays player's inventory\n \n"

                                    "Fullscreen\n"
                                    "Key: F12\n"
                                    "Results: switches between fullscreen mode and window mode\n \n"
                                    ).show();
}

}
