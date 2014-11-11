#include "CmdUse.h"
#include <functional>
#include "utils/selector_type.h"
#include "utils/target_selector/target_selector.h"
#include "Actor/Effects/Effect.h"
#include "utils/direction_selector.h"
#include "gui/gui.h"
#include "utils/messenger.h"
#include <engine.h>
#include <gui/widget/menu/items_menu.h>
#include <gui/widget/menu/label_menu_item.h>
#include <gui/message_box.h>

namespace amarlon {

CmdUse::CmdUse()
{
}

bool CmdUse::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'u' );
}

void CmdUse::execute(Actor *executor)
{  
  Actor* item = acquireItemToUse(executor);

  Engine::instance().render();

  if (item != nullptr && item->afPickable()->getEffect() != nullptr)
  {
    SelectorType selectorType = item->afPickable()->getEffect()->getSelectorType();
    TargetSelector* tSelector = TargetSelector::create(selectorType);

    if (tSelector != nullptr)
    {
      std::vector<Actor*> targets = tSelector->select(executor, &Engine::instance().currentMap());
      Pickable* toUse = item->afPickable();

      if ( toUse->use( executor, targets ) && toUse->getUsesCount() == 0)
      {
        Actor* toRemove = item->afPickable()->spilt(1);
        executor->afContainer()->remove( toRemove );
      }

      delete tSelector;
    }
  }
  else if ( item )
  {
    gui::msgBox(item->getName() + " is not usable.", gui::MsgType::Warning);
  }

}

Actor* CmdUse::acquireItemToUse(Actor* executor)
{
  Actor* item = nullptr;

  gui::ItemsMenu itemsMenu;
  itemsMenu.centerPosition();
  itemsMenu.setTitle("Choose item to use");

  std::function<bool(Actor*)> filter = [](Actor* a){ return a->afPickable() && a->afPickable()->getEffect(); };

  std::vector<Actor*> usableItems = executor->afContainer()->content(&filter);
  if ( !usableItems.empty() )
  {
    std::map<int, Actor*> mItems = itemsMenu.fillWithItems<gui::LabelMenuItem>( usableItems );
    auto choosen = mItems.find( itemsMenu.choose(*TCODConsole::root) );
    if ( choosen != mItems.end() ) item = choosen->second;
  }
  else gui::msgBox("You don't have any usable items!", gui::MsgType::Warning);

  if ( item != nullptr && item->afPickable()->isStackable() ) item = item->afPickable()->spilt(1);

  return item;
}

}
