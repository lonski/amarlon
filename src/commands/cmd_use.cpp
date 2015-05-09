#include "cmd_use.h"
#include <functional>
#include "utils/selector_type.h"
#include "utils/target_selector/target_selector.h"
#include "utils/direction_selector.h"
#include "utils/messenger.h"
#include "actor/effects/effect.h"
#include "engine.h"
#include "gui/gui.h"
#include "gui/widget/menu/items_menu.h"
#include "gui/widgets/alabel_menu_item.h"
#include "gui/message_box.h"

namespace amarlon {

CmdUse::CmdUse()
{
}

bool CmdUse::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'u' );
}

void CmdUse::execute()
{  
  Actor* item = acquireItemToUse();

  Engine::instance().render();

  if (item != nullptr && item->getFeature<Pickable>()->getEffect() != nullptr)
  {
    TargetSelector& tSelector = item->getFeature<Pickable>()->getEffect()->getTargetSelector();

    std::vector<Actor*> targets = tSelector.select();
    Pickable* toUse = item->getFeature<Pickable>();

    if ( toUse->use( Actor::Player, targets ) && toUse->getUsesCount() == 0)
    {
      Actor* toRemove = item->getFeature<Pickable>()->spilt(1);
      Actor::Player->getFeature<Container>()->remove( toRemove );
    }
  }
  else if ( item )
  {
    gui::msgBox(item->getName() + " is not usable.", gui::MsgType::Warning);
  }

}

Actor* CmdUse::acquireItemToUse()
{
  Actor* item = nullptr;

  gui::ItemsMenu itemsMenu;
  itemsMenu.setPosition(gui::AWidget::GAME_SCREEN_CENTER);
  itemsMenu.setTitle("Choose item to use");

  std::function<bool(Actor*)> filter = [](Actor* a){ return a->getFeature<Pickable>() && a->getFeature<Pickable>()->getEffect(); };

  std::vector<Actor*> usableItems = Actor::Player->getFeature<Container>()->content(&filter);
  if ( !usableItems.empty() )
  {
    std::map<int, Actor*> mItems = itemsMenu.fillWithItems<gui::ALabelMenuItem>( usableItems );
    auto choosen = mItems.find( itemsMenu.choose(*TCODConsole::root) );
    if ( choosen != mItems.end() ) item = choosen->second;
  }
  else gui::msgBox("You don't have any usable items!", gui::MsgType::Warning);

  if ( item != nullptr && item->getFeature<Pickable>()->isStackable() ) item = item->getFeature<Pickable>()->spilt(1);

  return item;
}

}
