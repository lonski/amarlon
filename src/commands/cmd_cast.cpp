#include "cmd_cast.h"
#include <message_box.h>
#include <actor.h>
#include <spell.h>
#include <cast_action.h>
#include <target_selector.h>

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
  //show a window to choose spell
  return Spell::Gateway.fetch( SpellId::CureLightWounds );
}

}
