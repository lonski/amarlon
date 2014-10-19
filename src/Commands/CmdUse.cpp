#include "CmdUse.h"
#include "Utils/SelectorType.h"
#include "Utils/TargetSelector/TargetSelector.h"
#include "Utils/InventoryManager.h"
#include "Actor/Effects/Effect.h"
#include "Utils/DirectionSelector.h"
#include "Gui/Gui.h"

CmdUse::CmdUse()
{
}

bool CmdUse::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'u' );
}

void CmdUse::execute(Map *map, Actor *executor)
{
  Actor* item = selectItemToUse(executor);

  if (item && item->afPickable()->getEffect())
  {
    SelectorType selectorType = item->afPickable()->getEffect()->getSelectorType();
    TargetSelector* tSelector = TargetSelector::create(selectorType);

    if (tSelector != nullptr)
    {
      std::vector<Actor*> targets = tSelector->select(executor, map);
      Pickable* toUse = item->afPickable();

      if ( toUse->use( executor, targets ) && toUse->getUsesCount() == 0)
      {
        Actor* toRemove = item->afPickable()->spilt(1);
        executor->afContainer()->remove( toRemove );
      }

      delete tSelector;
    }
  }
  else
  {
    Gui::Root.message(item->getName() + " is not usable.");
  }

}

Actor* CmdUse::selectItemToUse(Actor *executor)
{
  TCODConsole::root->saveApf("tmp");

  InventoryManager inv(executor);
  Actor* item = inv.chooseItemToUse();

  TCODConsole::root->loadApf("tmp");
  TCODConsole::root->flush();

  return item;
}
