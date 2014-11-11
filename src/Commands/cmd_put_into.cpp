#include "cmd_put_into.h"
#include <engine.h>
#include <world/map.h>
#include <Actor/Actor.h>
#include <gui/window/pick_up_window.h>

namespace amarlon {

bool CmdPutInto::accept(TCOD_key_t &key)
{
  return key.vk == TCODK_CHAR && key.c == 'p';
}

void CmdPutInto::execute(Actor *executor)
{
  Map& map = Engine::instance().currentMap();
  int x = executor->getX();
  int y = executor->getY();

  int dx(0), dy(0);


  _dSelector.select(dx, dy);

  Actor* target = map.getFirstActor(x+dx, y+dy);

  Engine::instance().windowManager()
                    .getWindow<gui::PickUpWindow>()
                    .setPicker(target)
                    .setContainer(Actor::Player->afContainer())
                    .show();

}

}
