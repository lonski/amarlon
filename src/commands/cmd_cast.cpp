#include "cmd_cast.h"
#include <message_box.h>
#include <actor.h>
#include <spell.h>
#include <cast_action.h>
#include <target_selector.h>
#include <menu_window.h>
#include <engine.h>
#include <world.h>
#include <map.h>
#include <spell_book.h>

namespace amarlon {

CmdCast::CmdCast()
{
}

bool CmdCast::accept(const TCOD_key_t& key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'C' );
}

int CmdCast::execute()
{
  int turns = 0;
  SpellPtr spell = getSpell();

  Engine::instance().render();
  TCODConsole::root->flush();

  if ( spell )
  {
     TargetSelectorPtr selector( TargetSelector::create( spell->getTargetType() ) );
     if ( selector )
     {
       selector->setRange( spell->getRange() );
       selector->setRadius( spell->getRadius() );
       MapPtr map = Engine::instance().getWorld().getCurrentMap();
       Target target = selector->select([&](ActorPtr a){ return map->isInFov(a->getX(), a->getY()); });

       if ( !Engine::instance().getPlayer()->performAction( new CastAction(spell, target) ) )
       {
         gui::msgBox("Failed to cast spell!", gui::MsgType::Warning);
       }
     }
     ++turns;
  }
  return turns;
}

SpellPtr CmdCast::getSpell()
{
  SpellPtr spell;
  CharacterPtr character = Engine::instance().getPlayer()->getFeature<Character>();

  if ( character && character->getSpellBook() )
  {
    auto spells = character->getSpellBook()->getSlots( [](SpellSlotPtr s){ return s->isPrepared && s->spell; } );
    if ( !spells.empty() )
    {
      gui::MenuWindow& window = Engine::instance().getWindowManager().getWindow<gui::MenuWindow>();
                       window . setPosition(gui::AWidget::GAME_SCREEN_CENTER);
                       window . setTitle("Choose spell to cast");
                       window . fill<SpellSlot>( spells, [](SpellSlotPtr s){ return s->spell->getName(); } );
                       window . show();

      if ( auto selected = window.getSelectedItem() ) spell = selected->getObject<SpellSlot>()->spell;
    }
    else
    {
      gui::msgBox("You don't have any prepared spells!", gui::MsgType::Warning);
    }
  }
  else
  {
    gui::msgBox("You don't know any spells!", gui::MsgType::Warning);
  }

  return spell;
}

}

