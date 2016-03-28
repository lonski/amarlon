#include "cmd_debug.h"
#include <message_box.h>
#include <engine.h>
#include <window_manager.h>
#include <menu_window.h>
#include <alabel_menu_item.h>
#include <playable_character.h>
#include <single_range_selector.h>
#include <fixed_size_text_window.h>
#include <input_dialog.h>
#include <direction_selector.h>
#include <map.h>

namespace amarlon {

CmdDebug::CmdDebug()
{
}

CmdDebug::~CmdDebug()
{
}

bool CmdDebug::accept(const TCOD_key_t &key)
{
  return key.vk == TCODK_CHAR && key.c == '~';
}

int CmdDebug::execute()
{
  gui::MenuWindow& menu = Engine::instance()
                        . getWindowManager()
                        . getWindow<gui::MenuWindow>();

  menu.setTitle("Debug menu");

  menu.addMenuItem( gui::ALabelMenuItemPtr(
                      new gui::ALabelMenuItem("Inspect actor",
                                              [&](){ inspectActor(); })) );

  menu.addMenuItem( gui::ALabelMenuItemPtr(
                      new gui::ALabelMenuItem("Advance player level",
                                              [&](){ advancePlayerLevel(); })) );

  menu.addMenuItem( gui::ALabelMenuItemPtr(
                      new gui::ALabelMenuItem("Create item",
                                              [&](){ createItem(); })) );

  menu.addMenuItem( gui::ALabelMenuItemPtr(
                      new gui::ALabelMenuItem("Toggle invisibility",
                                              [&](){ toggleInvisibility(); })) );

  menu.show();

  return 0;
}

void CmdDebug::inspectActor()
{
  SingleRangeSelector selector("Select a tile to inspect...");
  selector.setRange(666);
  Target target = selector.select();

  if (!target.actors.empty())
  {
    if ( target.actors.size() > 1 )
    {
      gui::MenuWindow& menu = Engine::instance()
                            . getWindowManager()
                            . getWindow<gui::MenuWindow>();
      menu.fill<Actor>(target.actors, [](ActorPtr a){ return a->getName();});
      menu.setTitle("Select actor to inspect");
      menu.show();

      auto s = menu.getSelectedItem();
      if ( s ) showInfo( s->getObject<Actor>() );
    }
    else
    {
      showInfo(target.actors.front());
    }
  }

}

void CmdDebug::advancePlayerLevel()
{
  auto player = Engine::instance().getPlayer();
  PlayableCharacterPtr c = player->getFeature<PlayableCharacter>();
  c->advanceLevel();
}

void CmdDebug::showInfo(ActorPtr a)
{
  if (a)
  {
    gui::FixedSizeTextWindow& wnd = Engine::instance()
                                  . getWindowManager()
                                  . getWindow<gui::FixedSizeTextWindow>();
    wnd.setWidth( Engine::screenWidth );
    wnd.setHeight( Engine::screenHeight );
    wnd.setPosition(0,0);
    wnd.setText( a->debug("#") );
    wnd.show();
  }

}

void CmdDebug::createItem()
{
  gui::InputDialog& wnd = Engine::instance()
                         . getWindowManager()
                         . getWindow<gui::InputDialog>();
  wnd.setTitle("Enter actor ID");
  wnd.show();

  ActorPtr player = Engine::instance().getPlayer();
  ActorPtr a = Actor::create( (ActorType)fromStr<int>(wnd.getText()) );

  Engine::instance().render();
  Engine::instance().flush();

  int dx(0), dy(0);
  DirectionSelector selector("Select a direction..");
  selector.select(dx, dy);

  a->setPosition(player->getX() + dx, player->getY() + dy);
  player->getMap()->addActor(a);
}

void CmdDebug::toggleInvisibility()
{
  ActorPtr player = Engine::instance().getPlayer();
  if ( player )
  {
    player->setVisible( !player->isVisible() );
  }
}

}
