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
  Darkvision      = 7,
  DwarfRacial     = 8,
  ElfRacial       = 9,
  HalflingRacial  = 10,
  HumanRacial     = 11,
};

}

#endif // SKILL_ID

