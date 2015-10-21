#ifndef SKILL_ID
#define SKILL_ID

#include <string>
#include <target_type.h>

namespace amarlon {

enum class SkillId
{
  Null            = 0,
  OpenLocks       = 1,
  DisarmTraps     = 2,
  Hide            = 3,
  PickPockets     = 4,  //TODO - needs NPC's
  SilentMove      = 5,
  FindTraps       = 6,
  Darkvision      = 7,  //TODO - passive skill
  DwarfRacial     = 8,  //TODO - passive skill
  ElfRacial       = 9,  //TODO - passive skill
  HalflingRacial  = 10, //TODO - passive skill
  HumanRacial     = 10, //TODO - passive skill
};

static inline std::string SkillId2Str(SkillId t)
{
  std::string str = "";
  switch ( t )
  {
    case SkillId::OpenLocks: str = "Open locks"; break;
    case SkillId::DisarmTraps: str = "Disarm/arm traps"; break;
    case SkillId::Hide: str = "Hide"; break;
    case SkillId::PickPockets: str = "Pick pockets"; break;
    case SkillId::SilentMove: str = "Silent move"; break;
    case SkillId::FindTraps: str = "Find traps"; break;
    default:;
  }
  return str;
}

static inline TargetType SkillId2TargetType(SkillId t)
{
  TargetType type = TargetType::SELF;
  switch ( t )
  {
    case SkillId::OpenLocks:   type = TargetType::SINGLE_NEIGHBOUR; break;
    case SkillId::DisarmTraps: type = TargetType::SINGLE_NEIGHBOUR; break;
    case SkillId::Hide:        type = TargetType::SELF;             break;
    case SkillId::PickPockets: type = TargetType::SINGLE_NEIGHBOUR; break;
    case SkillId::SilentMove:  type = TargetType::SELF;             break;
    case SkillId::FindTraps:   type = TargetType::CASTER_AREA;      break;
    default:;
  }
  return type;
}

}

#endif // SKILL_ID

