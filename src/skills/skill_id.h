#ifndef SKILL_ID
#define SKILL_ID

#include <string>

namespace amarlon {

enum class SkillId
{
  Null        = 0,
  OpenLocks   = 1,
  RemoveTraps = 2,
  Hide        = 3,
  PickPockets = 4,
  SilentMove  = 5
};


static inline std::string SkillId2Str(SkillId t)
{
  std::string str = "";
  switch ( t )
  {
    case SkillId::OpenLocks: str = "Open locks"; break;
    case SkillId::RemoveTraps: str = "Remove traps"; break;
    case SkillId::Hide: str = "Hide"; break;
    case SkillId::PickPockets: str = "Pick pockets"; break;
    case SkillId::SilentMove: str = "Silent move"; break;
    default:;
  }
  return str;
}

}

#endif // SKILL_ID

