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

namespace amarlon {

CmdCast::CmdCast()
{
}

bool CmdCast::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'C' );
}

int CmdCast::execute()
{
  int turns = 0;
  SpellPtr spell = getSpell();
  Engine::instance().render();
  if ( spell )
  {
     TargetSelectorPtr selector( TargetSelector::create( spell->getTargetType() ) );
     if ( selector )
     {
       selector->setRange( spell->getRange() );
       selector->setRadius( spell->getRadius() );
       MapPtr map = Engine::instance().getWorld().getCurrentMap();
       ActorActionPtr action( new CastAction(spell, selector->select([&](ActorPtr a){ return map->isInFov(a->getX(), a->getY()); })) );
       if ( !Engine::instance().getPlayer()->performAction( action ) )
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

  gui::MenuWindow& window = Engine::instance().getWindowManager().getWindow<gui::MenuWindow>();
                   window . setPosition(gui::AWidget::GAME_SCREEN_CENTER);
                   window . setTitle("Choose spell to cast");

  if ( character && !character->getSpells().empty() )
  {
    window.fill<Spell>( character->getSpells(), [](SpellPtr s){ return s->getName(); } );
    window.show();
    if ( auto selected = window.getSelectedItem() )
    {
      spell = selected->getObject<Spell>();
    }
  }
  else gui::msgBox("You don't know any spells!", gui::MsgType::Warning);

  return spell;
}

}

