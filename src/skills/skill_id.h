#ifndef SKILL_ID
#define SKILL_ID

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

}

#endif // SKILL_ID

