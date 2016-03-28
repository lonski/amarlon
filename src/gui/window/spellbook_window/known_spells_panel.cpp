#include "known_spells_panel.h"
#include <amenu.h>
#include <alabel_menu_item.h>
#include <spellbook_window.h>
#include <spell_level_panel.h>
#include <spell.h>
#include <engine.h>
#include <fixed_size_text_window.h>

namespace amarlon { namespace gui {

KnownSpellsPanel::KnownSpellsPanel(SpellBookWindow& parent)
  : ASubPanel(27, 33)
  , _spells(new AMenu)
  , _parent(parent)
{
  setFrameColor(TCODColor::desaturatedOrange);
  setTitleColor(TCODColor::black);
  setFrame(true);
  setTitle("Known spells");

  _spells->setPosition(1,2);
  addWidget(_spells);
}

void KnownSpellsPanel::selectNext()
{
  _spells->selectNext();
}

void KnownSpellsPanel::selectPrevious()
{
  _spells->selectPrevious();
}

void KnownSpellsPanel::setSpellBook(SpellBookPtr spellbook)
{
  _spellbook = spellbook;
}

void KnownSpellsPanel::activate()
{
  ASubPanel::activate();
  setFrameColor(TCODColor::orange);
}

void KnownSpellsPanel::deactivate()
{
  ASubPanel::deactivate();
  setFrameColor(TCODColor::desaturatedOrange);
}

void KnownSpellsPanel::update()
{
  _spells->removeAllItems();

  if (_spellbook)
  {
    int level = _parent.getLevelsPanel().getSelectedLevel();
    auto spells = _spellbook->getKnownSpells([&level](SpellPtr s){return s->getLevel() == level;});
    for ( auto s : spells )
    {
      auto* item = new ALabelMenuItem( s->getName() );
      item->setObject<Spell>(s);
      _spells->addItem( AMenuItemPtr(item) );
    }
  }
}

void KnownSpellsPanel::manage()
{
  auto item = _spells->getSelectedItem();
  if ( item )
  {
    SpellPtr spell = item->getObject<Spell>();
    if ( spell )
    {
      auto& window = Engine::instance()
                   .getWindowManager()
                   .getWindow<FixedSizeTextWindow>();
            window .setText( spell->getDescription() );
            window .setPosition(AWindow::GAME_SCREEN_CENTER);
            window .show();
    }
  }
}

}}
