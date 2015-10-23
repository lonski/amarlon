#include "game_menu_window.h"
#include <load_save_game_window.h>
#include <engine.h>
#include <world.h>
#include <aslot_menu_item.h>
#include <fstream>
#include <character_creation_window.h>

namespace amarlon { namespace gui {

GameMenu::GameMenu()
  : _menu( new AMenu )
  , _logo( new AList )
{
  setWidth ( Engine::screenWidth );
  setHeight( Engine::screenHeight );
  setPosition(0,0);
  setFrame(false);

  _logo->setPosition(10,15);
  _logo->pushBack(ColoredString("                               _ ", TCODColor::lightRed));
  _logo->pushBack(ColoredString("    /\\                        | |", TCODColor::lightRed));
  _logo->pushBack(ColoredString("   /  \\   _ __ ___   __ _ _ __| | ___  _ __", TCODColor::lightRed));
  _logo->pushBack(ColoredString("  / /\\ \\ | '_ ` _ \\ / _` | '__| |/ _ \\| '_ \\", TCODColor::lightRed));
  _logo->pushBack(ColoredString(" / ____ \\| | | | | | (_| | |  | | (_) | | | |", TCODColor::lightRed));
  _logo->pushBack(ColoredString("/_/    \\_\\_| |_| |_|\\__,_|_|  |_|\\___/|_| |_|", TCODColor::lightRed));
  _logo->pushBack(ColoredString(" ", TCODColor::red));
  _logo->pushBack(ColoredString("An ASCII based cRPG", TCODColor::red));

  addWidget(_logo);
  addWidget(_menu);

  _functions["New"]  = &GameMenu::new_game;
  _functions["Save"] = &GameMenu::save_game;
  _functions["Load"] = &GameMenu::load_game;
  _functions["Quit"] = &GameMenu::quit_game;
}

GameMenu::~GameMenu()
{
}

void GameMenu::fillMenuSlots()
{
  _menu->removeAllItems();

  _menu->addItem( AMenuItemPtr( new ASlotMenuItem(20, "", "New", "", TCODColor::darkerAmber) ) );
  if ( Engine::instance().isRunning() )
    _menu->addItem( AMenuItemPtr( new ASlotMenuItem(20, "", "Save", "", TCODColor::darkerAmber) ) );
  _menu->addItem( AMenuItemPtr( new ASlotMenuItem(20, "", "Load", "", TCODColor::darkerAmber) ) );
  _menu->addItem( AMenuItemPtr( new ASlotMenuItem(20, "", "Quit", "", TCODColor::darkerAmber) ) );

  _menu->setPosition(Engine::screenWidth - 30,
                     Engine::screenHeight - ( _menu->getItemCount() * 5 ) - 10);
}

bool GameMenu::new_game()
{
  Engine::instance().prologue();
  Engine::instance().getWindowManager().getWindow<CharacterCreationWindow>().show();

  return true;
}

bool GameMenu::save_game()
{
  auto& window = Engine::instance().getWindowManager().getWindow<LoadSaveGameWindow>();
  window.setMode( LoadSaveGameWindow::SAVE );
  window.show();

  std::string fn = window.getSelectedFilename();
  if ( !fn.empty() )
  {
    //store save game header
    std::ofstream save(fn, std::ios_base::out | std::ofstream::trunc);
    save << "<!-- " << std::endl
         << window.getSelectedSlotName() << std::endl
         << "--> " << std::endl;

    //store world
    Engine::instance().getWorld().store(fn);

    return true;
  }
  return false;
}

bool GameMenu::load_game()
{
  auto& window = Engine::instance().getWindowManager().getWindow<LoadSaveGameWindow>();
  window.setMode( LoadSaveGameWindow::LOAD );
  window.show();

  std::string fn = window.getSelectedFilename();
  if ( !fn.empty() )
  {
    Engine::instance().prologue();
    Engine::instance().enterGame(fn);
    return true;
  }
  return false;
}

bool GameMenu::quit_game()
{
  Engine::instance().quit();
  return true;
}

AWindow& GameMenu::show()
{
  TCODConsole& console = *TCODConsole::root;
  TCOD_key_t key;
  bool exit = false;

  fillMenuSlots();
  _menu->selectNext();

  while( !(exit) && !(TCODConsole::isWindowClosed()) )
  {
    render(console);
    console.flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    switch ( key.vk )
    {
      case TCODK_DOWN:
      case TCODK_KP2:
      {
        _menu->selectNext();
        break;
      }
      case TCODK_UP:
      case TCODK_KP8:
      {
        _menu->selectPrevious();
        break;
      }
      case TCODK_ENTER:
      case TCODK_KPENTER:
      {
        auto item = _menu->getSelectedItem();
        auto fun = _functions[ item->getValue() ];

        exit = (this->*fun)();

        break;
      }
      case TCODK_ESCAPE:
      {
        exit = Engine::instance().isRunning();
        break;
      }

      default:;
    }
  }

  return *this;
}

}}
