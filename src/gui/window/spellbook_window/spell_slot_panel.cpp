#include "spell_slot_panel.h"
#include <amenu.h>
#include <aslot_menu_item.h>
#include <spellbook_window.h>
#include <spell_level_panel.h>
#include <spell_slot.h>
#include <spell.h>
#include <message_box.h>
#include <engine.h>
#include <window_manager.h>
#include <menu_window.h>

namespace amarlon { namespace gui {

SpellSlotPanel::SpellSlotPanel(SpellBookWindow &parent)
  : ASubPanel(27, 33)
  , _slots(new AMenu)
  , _parent(parent)
{
  setFrameColor(TCODColor::desaturatedOrange);
  setTitleColor(TCODColor::black);
  setFrame(true);
  setTitle("Prepared spells");

  _slots->setPosition(1,2);
  addWidget(_slots);
}

void SpellSlotPanel::selectNext()
{
  _slots->selectNext();
}

void SpellSlotPanel::selectPrevious()
{
  _slots->selectPrevious();
}

void SpellSlotPanel::setSpellBook(SpellBookPtr spellbook)
{
  _spellbook = spellbook;
}

void SpellSlotPanel::activate()
{
  ASubPanel::activate();
  setFrameColor(TCODColor::orange);
}

void SpellSlotPanel::deactivate()
{
  ASubPanel::deactivate();
  setFrameColor(TCODColor::desaturatedOrange);
}

void SpellSlotPanel::update()
{
  if ( _spellbook )
  {
    _slots->removeAllItems();

    int level = _parent.getLevelsPanel().getSelectedLevel();
    auto sSlots = _spellbook->getSlots([&level](SpellSlotPtr slot){ return slot->level == level; });

    for (auto s : sSlots)
    {
      std::string name = s->spell ? s->spell->getName() : "";
      TCODColor color = !s->isPrepared && s->spell ? TCODColor::lightGrey : TCODColor::darkYellow;
      TCODColor textColor = !s->isPrepared && s->spell ? TCODColor::lightGrey : TCODColor::white;

      auto* item = new ASlotMenuItem(25, name, "", "", color);
      item->setNameColor(textColor);
      item->setObject<SpellSlot>(s);
      _slots->addItem( AMenuItemPtr( item ) );
    }
  }
}

void SpellSlotPanel::manage()
{
  auto item = _slots->getSelectedItem();
  if ( item )
  {
    SpellSlotPtr slot = item->getObject<SpellSlot>();
    if ( slot )
    {
      //Clear slot
      if (    ( slot->isPrepared && slot->spell && questionBox("Remove prepared spell?") == QuestionDialog::YES )
           || ( !slot->isPrepared && slot->spell )
         )
      {
        slot->clear();
        update();
      }
      //assign known spell to slot
      else if ( !slot->spell )
      {

        int level = _parent.getLevelsPanel().getSelectedLevel();
        auto spells = _spellbook->getKnownSpells([&level](SpellPtr s){return s->getLevel() == level;});

        gui::MenuWindow& window = Engine::instance().getWindowManager().getWindow<gui::MenuWindow>();
                         window . setPosition(gui::AWidget::GAME_SCREEN_CENTER);
                         window . setTitle("Choose spell to prepare");
                         window.fill<Spell>( spells , [](SpellPtr s){ return s->getName(); } );
                         window.show();

        if ( auto selected = window.getSelectedItem() )
        {
          auto spell = selected->getObject<Spell>();
          if ( spell )
          {
            slot->isPrepared = false;
            slot->spell = selected->getObject<Spell>();
            update();
          }
        }
      }
    }
  }
}

}}
