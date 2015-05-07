#include "items_menu.h"

namespace amarlon { namespace gui {

ItemsMenu::ItemsMenu(const int &width, const int &height)
  : Menu(width, height)
{
  setPosition(gui::AWidget::GAME_SCREEN_CENTER);
}

}}
