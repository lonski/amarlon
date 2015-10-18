#include "cmd_use_skill.h"
#include <skill.h>
#include <engine.h>
#include <menu_window.h>
#include <window_manager.h>
#include <actor.h>
#include <message_box.h>
#include <target_selector.h>
#include <world.h>
#include <map.h>
#include <use_skill_action.h>

namespace amarlon {

CmdUseSkill::CmdUseSkill()
{
}

bool CmdUseSkill::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'U' );
}

int CmdUseSkill::execute()
{
  int turns(0);

  if ( SkillPtr skill = getSkill() )
  {
    Engine::instance().render();
    TCODConsole::root->flush();

    TargetSelectorPtr selector( TargetSelector::create( skill->getTargetType() ) );
    if ( selector )
    {
      MapPtr map = Engine::instance().getWorld().getCurrentMap();
      ActorActionPtr action( new UseSkillAction(skill, selector->select([&](ActorPtr a){ return map->isInFov(a->getX(), a->getY()); })) );
      if ( !Engine::instance().getPlayer()->performAction( action ) )
      {
        gui::msgBox(skill->getName() + " failed!", gui::MsgType::Warning);
      }
      ++turns;
    }
  }

  return turns;
}

SkillPtr CmdUseSkill::getSkill()
{
  SkillPtr skill;

  auto skills = Engine::instance().getPlayer()->getFeature<Character>()->getSkills();
  if ( !skills.empty() )
  {
    gui::MenuWindow& window = Engine::instance().getWindowManager().getWindow<gui::MenuWindow>();
                     window . setPosition(gui::AWidget::GAME_SCREEN_CENTER);
                     window . setTitle("Choose skill to use");
                     window . fill<Skill>( skills, [](SkillPtr s){ return s->getName(); } );
                     window . show();

    if ( auto selected = window.getSelectedItem() )
    {
      skill = selected->getObject<Skill>();
    }
  }
  else gui::msgBox("You don't have any skills!", gui::MsgType::Warning);

  return skill;
}

}
