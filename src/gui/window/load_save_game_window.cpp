#include "load_save_game_window.h"
#include <engine.h>
#include <fstream>
#include <aslot_menu_item.h>
#include <input_dialog.h>

namespace amarlon { namespace gui {

LoadSaveGameWindow::LoadSaveGameWindow()
  : _menu( new AMenu )
  , _mode(LOAD)
  , _slotCount(10)
  , _title(new ALabel)
{
  addWidget(_menu);
  addWidget(_title);
}

LoadSaveGameWindow::~LoadSaveGameWindow()
{
}

AWindow &LoadSaveGameWindow::show()
{
  TCODConsole* console = Engine::instance().getConsole();
  if ( console )
  {
    TCOD_key_t key;
    bool exit = false;

    _menu->selectNext();

    while( !(exit) && !(TCODConsole::isWindowClosed()) )
    {
      render(*console);
      console->flush();

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
          if ( _mode == SAVE )
          {
            auto item = _menu->getSelectedItem();
            if ( item )
            {
              item->setValue( promptForName( item->getValue() ) );
            }
          }
          exit = true;
          break;
        }
        case TCODK_ESCAPE:
        {
          _menu->deselect();
          exit = true;
          break;
        }

        default:;
      }
    }
  }

  return *this;
}

std::string LoadSaveGameWindow::getSelectedFilename()
{
  auto item = std::dynamic_pointer_cast<ASlotMenuItem>(_menu->getSelectedItem());
  if ( item )
  {
    std::string fn = item->getName();
    std::replace_if(fn.begin(), fn.end(),[](char c){ return c== ' ';}, '_');
    fn =  "saves/"+fn+".sav";

    return std::ifstream(fn) || _mode == SAVE ? fn : "";
  }
  return "";
}

std::string LoadSaveGameWindow::getSelectedSlotName()
{
  auto item = _menu->getSelectedItem();
  return item ? item->getValue() : "";
}

void LoadSaveGameWindow::setMode(LoadSaveGameWindow::Mode mode)
{
  _mode = mode;
  _title->setValue( _mode == LOAD ? "Load saved game:" : "Choose slot to save the game:" );
  _title->setPosition(AWindow::WINDOW_CENTER);
  _title->setPosition(_title->getX(), 8);
}

AWindow &LoadSaveGameWindow::setDefaults()
{
  setWidth ( Engine::screenWidth );
  setHeight( Engine::screenHeight );
  setPosition(0,0);
  setFrame(false);
  fillSaveSlots();

  return *this;
}

void LoadSaveGameWindow::fillSaveSlots()
{
  _menu->removeAllItems();
  for ( int i = 1; i <= _slotCount; ++i )
  {
    std::string name = "<Empty>";
    std::ifstream in("saves/Slot_"+toStr(i)+".sav");
    if ( in.is_open() )
    {
      std::string line;
      while ( std::getline(in, line) ) { if (line.find("<!--") != std::string::npos ) { break; } }
      std::getline(in, name);
    }
    _menu->addItem( AMenuItemPtr( new ASlotMenuItem(80, "Slot "+toStr(i), name, ":", TCODColor::darkerFlame) ) );
  }
  _menu->setPosition(AWindow::WINDOW_CENTER);
}

std::string LoadSaveGameWindow::promptForName(const std::string& def)
{
  auto& input = Engine::instance().getWindowManager().getWindow<InputDialog>();
  input.setPosition(AWindow::WINDOW_CENTER);
  input.setTitle("Enter save game name");
  input.setMaxSize(50);
  input.setWidth(60);
  input.setText(def);
  input.show();

  return input.getText().empty() ? "No Name" : input.getText();
}

}}
