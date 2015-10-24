#include "spellbook_window.h"
#include <spell_book.h>
#include <spell_level_panel.h>
#include <spell_slot_panel.h>
#include <known_spells_panel.h>
#include <engine.h>

namespace amarlon { namespace gui {

SpellBookWindow::SpellBookWindow()
  : _levels(new SpellLevelPanel(*this))
  , _slots(new SpellSlotPanel(*this))
  , _known(new KnownSpellsPanel(*this))
{
  _activePanel = LEVELS;

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

void SpellBookWindow::managePanel(int panel)
{
  switch( panel)
  {
    case SLOTS: _slots->manage(); break;
    case KNOWN: _known->manage(); break;
    default:;
  }
}

bool SpellBookWindow::exitWindow(TCOD_key_t key)
{
  return ( (key.vk == TCODK_CHAR && key.c == 'S') || (key.vk == TCODK_ESCAPE) );
}

void SpellBookWindow::loopUpdate()
{
  Engine::instance().render();
}

}}

