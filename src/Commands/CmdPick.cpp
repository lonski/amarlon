#include "CmdPick.h"
#include <Utils/ItemPicker.h>
#include <Gui/AmountWindow.h>
#include <Actor/ActorFeatures/Container.h>
#include <algorithm>
#include "World/Map.h"
#include "Engine.h"

CmdPick::CmdPick()
{
}

bool CmdPick::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == ',' );
}

void CmdPick::execute(Engine *engine, Actor *executor)
{
  Map* map = engine->currentMap();
  std::vector<Actor*> items = map->getActors(executor->getX(), executor->getY(),
                              [](Actor* a) -> bool
                              {
                                return a->afPickable();
                              });

  ItemPicker picker(items, executor);
  items = picker.pick();

  std::for_each(items.begin(), items.end(), [&](Actor* a)
  {
    map->removeActor(a);
  });
}

void CmdPick::execute(Container* container, Actor *executor, bool forceGui)
{
  std::vector<Actor*> items = container->content();
  ItemPicker picker(items, executor);
  std::vector<Actor*> itemsPicked = picker.pick(forceGui);

  std::for_each(itemsPicked.begin(), itemsPicked.end(), [&](Actor* a)
  {
    container->remove(a);
  });
}
