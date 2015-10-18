#include "cmd_use_skill.h"
#include <skill.h>
#include <engine.h>
#include <menu_window.h>
#include <window_manager.h>
#include <actor.h>
#include <message_box.h>

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
    //TODO
    ++turns;
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
