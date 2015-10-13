#include "spellbook_window.h"
#include <spell_book.h>
#include <spell_level_panel.h>
#include <spell_slot_panel.h>
#include <known_spells_panel.h>
#include <engine.h>

namespace amarlon { namespace gui {

SpellBookWindow::SpellBookWindow()
  : _activePanel(LEVELS)
  , _levels(new SpellLevelPanel(*this))
  , _slots(new SpellSlotPanel(*this))
  , _known(new KnownSpellsPanel(*this))
{
  setHeight( 36 );
  setWidth( 63 );
  setFrame(true);
  setTitle("Spellbook");
  setPosition(AWindow::GAME_SCREEN_CENTER);

  _levels->setPosition(1,2);
  _slots->setPosition( _levels->getWidth() + 1 ,2);
  _known->setPosition( _slots->getWidth() + _slots->getX() ,2);

  addWidget(_levels);
  addWidget(_slots);
  addWidget(_known);

  _panels[ LEVELS ] = _levels;
  _panels[ SLOTS  ] = _slots;
  _panels[ KNOWN  ] = _known;

  _levels->activate();
}

SpellBookWindow::~SpellBookWindow()
{
}

SpellBookWindow &SpellBookWindow::setSpellBook(SpellBookPtr spellbook)
{
  _spellbook = spellbook;

  _slots->setSpellBook(_spellbook);
  _slots->update();

  _known->setSpellBook(_spellbook);
  _known->update();

  return *this;
}

AWindow &SpellBookWindow::show()
{
  TCOD_key_t key;

  while( !TCODConsole::isWindowClosed() )
  {
    Engine::instance().render();
    render(*TCODConsole::root);
    TCODConsole::root->flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    handleKey(key);

    if ( (key.vk == TCODK_CHAR && key.c == 'S') || (key.vk == TCODK_ESCAPE) )
      break;
  }

  return *this;
}

SpellLevelPanel &SpellBookWindow::getLevelsPanel()
{
  return *_levels;
}

SpellSlotPanel &SpellBookWindow::getSlotsPanel()
{
  return *_slots;
}

KnownSpellsPanel &SpellBookWindow::getKnownSpellsPanel()
{
  return *_known;
}

void SpellBookWindow::handleKey(TCOD_key_t key)
{
  switch ( key.vk )
  {
    case TCODK_TAB:
    {
      activateNextPanel();
      break;
    }
    case TCODK_DOWN:
    case TCODK_KP2:
    {
      _panels[_activePanel]->selectNext();
      break;
    }
    case TCODK_UP:
    case TCODK_KP8:
    {
      _panels[_activePanel]->selectPrevious();
      break;
    }
    case TCODK_LEFT:
    case TCODK_KP4:
    {
      do
      {
        activatePreviousPanel();
      }
      while ( !_panels[ _activePanel ]->isActivable() );
      break;
    }
    case TCODK_RIGHT:
    case TCODK_KP6:
    {
      do
      {
        activateNextPanel();
      }
      while ( !_panels[ _activePanel ]->isActivable() );
      break;
    }
    case TCODK_ENTER:
    case TCODK_KPENTER:
    {
      switch( _activePanel)
      {
        case SLOTS: _slots->manage(); break;
        case KNOWN: _known->manage(); break;
        default:;
      }
      break;
    }
    default:;
  }
}

void SpellBookWindow::activateNextPanel()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  cPanel->second->deactivate();

  if ( ++cPanel == _panels.end() ) cPanel = _panels.begin();

  _activePanel = cPanel->first;
  cPanel->second->activate();
}

void SpellBookWindow::activatePreviousPanel()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  cPanel->second->deactivate();

  if ( cPanel != _panels.begin()  )
    --cPanel;
  else
    std::advance(cPanel, _panels.size() - 1 );

  _activePanel = cPanel->first;
  cPanel->second->activate();
}

}}

