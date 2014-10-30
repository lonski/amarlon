#include "CmdUse.h"
#include <functional>
#include "Utils/SelectorType.h"
#include "Utils/TargetSelector/TargetSelector.h"
#include "Actor/Effects/Effect.h"
#include "Utils/DirectionSelector.h"
#include "Gui/Gui.h"
#include "Utils/Messenger.h"
#include "Engine.h"
#include <Gui/Widget/menu/items_menu.h>
#include <Gui/Widget/menu/label_menu_item.h>
#include <Gui/message_box.h>

namespace amarlon {

CmdUse::CmdUse()
{
}

bool CmdUse::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'u' );
}

void CmdUse::execute(Engine *engine, Actor *executor)
{  
  Actor* item = acquireItemToUse(executor, engine);

  engine->render();

  if (item && item->afPickable()->getEffect())
  {
    SelectorType selectorType = item->afPickable()->getEffect()->getSelectorType();
    TargetSelector* tSelector = TargetSelector::create(selectorType);

    if (tSelector != nullptr)
    {
      std::vector<Actor*> targets = tSelector->select(executor, engine->currentMap());
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
    Messenger::message()->actorNotUsable(item);
  }

}

Actor* CmdUse::acquireItemToUse(Actor* executor, Engine* engine)
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
    auto choosen = mItems.find( itemsMenu.choose(*engine->getConsole()) );
    if ( choosen != mItems.end() ) item = choosen->second;
  }
  else gui::msgError("You don't have any usable items!");

  if ( item && item->afPickable()->isStackable() ) item = item->afPickable()->spilt(1);

  return item;
}

}
