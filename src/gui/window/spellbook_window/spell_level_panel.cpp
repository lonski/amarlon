#include "spell_level_panel.h"
#include <amenu.h>
#include <aslot_menu_item.h>
#include <spellbook_window.h>
#include <spell_slot_panel.h>
#include <known_spells_panel.h>

namespace amarlon { namespace gui {

SpellLevelPanel::SpellLevelPanel(SpellBookWindow& parent)
  : ASubPanel(7, 33)
  , _levels(new AMenu)
  , _parent(parent)
{
  setFrameColor(TCODColor::desaturatedOrange);
  setTitleColor(TCODColor::black);
  setFrame(true);
  setTitle("Lv.");

  _levels->addItem( AMenuItemPtr( new ASlotMenuItem(5, "1","","") ) );
  _levels->addItem( AMenuItemPtr( new ASlotMenuItem(5, "2","","") ) );
  _levels->addItem( AMenuItemPtr( new ASlotMenuItem(5, "3","","") ) );
  _levels->addItem( AMenuItemPtr( new ASlotMenuItem(5, "4","","") ) );
  _levels->addItem( AMenuItemPtr( new ASlotMenuItem(5, "5","","") ) );
  _levels->addItem( AMenuItemPtr( new ASlotMenuItem(5, "6","","") ) );

  _levels->setPosition(1,2);
  addWidget(_levels);
}

void SpellLevelPanel::selectNext()
{
  _levels->selectNext();
  _parent.getSlotsPanel().update();
  _parent.getKnownSpellsPanel().update();
}

void SpellLevelPanel::selectPrevious()
{
  _levels->selectPrevious();
  _parent.getSlotsPanel().update();
  _parent.getKnownSpellsPanel().update();
}

void SpellLevelPanel::activate()
{
  ASubPanel::activate();
  setFrameColor(TCODColor::orange);
}

void SpellLevelPanel::deactivate()
{
  ASubPanel::deactivate();
  setFrameColor(TCODColor::desaturatedOrange);
}

int SpellLevelPanel::getSelectedLevel()
{
  ASlotMenuItemPtr item = std::dynamic_pointer_cast<ASlotMenuItem>( _levels->getSelectedItem() );
  return item ? fromStr<int>(item->getName()) : 0;
}

}}

