#include "cmd_cast.h"
#include <message_box.h>
#include <actor.h>
#include <spell.h>
#include <cast_action.h>
#include <target_selector.h>
#include <menu_window.h>
#include <engine.h>

namespace amarlon {

CmdCast::CmdCast()
{
}

bool CmdCast::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'C' );
}

void CmdCast::execute()
{
  SpellPtr spell = getSpell();
  Engine::instance().render();
  if ( spell )
  {
     TargetSelectorPtr selector( TargetSelector::create( spell->getTargetType() ) );
     if ( selector )
     {
       ActorActionPtr action( new CastAction(spell, selector->select()) );
       if ( !Actor::Player->performAction( action ) )
       {
         gui::msgBox("Failed to cast spell!", gui::MsgType::Warning);
       }
     }
  }
}

SpellPtr CmdCast::getSpell()
{
  SpellPtr spell;

  CharacterPtr character = Actor::Player->getFeature<Character>();

  gui::MenuWindow& window = Engine::instance().windowManager().getWindow<gui::MenuWindow>();
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
