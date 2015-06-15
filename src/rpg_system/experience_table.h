#ifndef EXPERIENCE_TABLE_H
#define EXPERIENCE_TABLE_H

#include <dices.h>
#include <character_classes.h>
#include <map>

namespace amarlon
{

typedef int SpellLevel;
typedef int SpellCount;

struct LevelData
{
  LevelData(int i_expNeeded, dices::Dice i_hitDice, int i_hpBonus, bool i_applyConModifier, std::map<SpellLevel, SpellCount> i_spellSlotCount)
    : expNeeded(i_expNeeded)
    , hitDice(i_hitDice)
    , hpBonus(i_hpBonus)
    , applyConModifier(i_applyConModifier)
    , spellSlotCount(i_spellSlotCount)
  {}

  LevelData(int i_expNeeded, dices::Dice i_hitDice, int i_hpBonus, bool i_applyConModifier)
    : expNeeded(i_expNeeded)
    , hitDice(i_hitDice)
    , hpBonus(i_hpBonus)
    , applyConModifier(i_applyConModifier)
  {}

  LevelData()
    : expNeeded(0)
    , hitDice(dices::NoDice)
    , hpBonus(0)
    , applyConModifier(false)
  {}

  int expNeeded;
  dices::Dice hitDice;
  int hpBonus;
  bool applyConModifier;
  std::map<SpellLevel, SpellCount> spellSlotCount;
};

namespace Experience
{
  const int MAX_LEVEL = 20;

  LevelData getLevelData(CharacterClass charClass, int level);

  static std::map<CharacterClass, std::map<int, LevelData> > expData = {
    {
      {
        CharacterClass::Fighter,
        {
        /*LV             EXP     HitDice       HP  */
          {1,  LevelData{0      ,dices::D8,    0, true} },
          {2,  LevelData{2000   ,dices::D8,    0, true} },
          {3,  LevelData{4000   ,dices::D8,    0, true} },
          {4,  LevelData{8000   ,dices::D8,    0, true} },
          {5,  LevelData{16000  ,dices::D8,    0, true} },
          {6,  LevelData{32000  ,dices::D8,    0, true} },
          {7,  LevelData{64000  ,dices::D8,    0, true} },
          {8,  LevelData{120000 ,dices::D8,    0, true} },
          {9,  LevelData{240000 ,dices::D8,    0, true} },
          {10, LevelData{360000 ,dices::NoDice,2, false} },
          {11, LevelData{480000 ,dices::NoDice,2, false} },
          {12, LevelData{600000 ,dices::NoDice,2, false} },
          {13, LevelData{720000 ,dices::NoDice,2, false} },
          {14, LevelData{840000 ,dices::NoDice,2, false} },
          {15, LevelData{960000 ,dices::NoDice,2, false} },
          {16, LevelData{1080000,dices::NoDice,2, false} },
          {17, LevelData{1200000,dices::NoDice,2, false} },
          {18, LevelData{1320000,dices::NoDice,2, false} },
          {19, LevelData{1440000,dices::NoDice,2, false} },
          {20, LevelData{1560000,dices::NoDice,2, false} },
        }
      },

      {
        CharacterClass::Thief,
        {
        /*LV             EXP     HitDice       HP  */
          {1,  LevelData{0      ,dices::D4,    0, true} },
          {2,  LevelData{1250   ,dices::D4,    0, true} },
          {3,  LevelData{2500   ,dices::D4,    0, true} },
          {4,  LevelData{5000   ,dices::D4,    0, true} },
          {5,  LevelData{10000  ,dices::D4,    0, true} },
          {6,  LevelData{20000  ,dices::D4,    0, true} },
          {7,  LevelData{40000  ,dices::D4,    0, true} },
          {8,  LevelData{75000  ,dices::D4,    0, true} },
          {9,  LevelData{150000 ,dices::D4,    0, true} },
          {10, LevelData{225000 ,dices::NoDice,2, false} },
          {11, LevelData{300000 ,dices::NoDice,2, false} },
          {12, LevelData{375000 ,dices::NoDice,2, false} },
          {13, LevelData{450000 ,dices::NoDice,2, false} },
          {14, LevelData{525000 ,dices::NoDice,2, false} },
          {15, LevelData{600000 ,dices::NoDice,2, false} },
          {16, LevelData{675000 ,dices::NoDice,2, false} },
          {17, LevelData{750000 ,dices::NoDice,2, false} },
          {18, LevelData{825000 ,dices::NoDice,2, false} },
          {19, LevelData{900000 ,dices::NoDice,2, false} },
          {20, LevelData{975000 ,dices::NoDice,2, false} },
        }
      },

      {
        CharacterClass::Cleric,
        {
        /*LV             EXP     HitDice       HP        SPELL1 SPELL2 SPELL3 SPELL4 SPELL5 SPELL6   */
          {1,  LevelData{0      ,dices::D6,    0, true, {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}} } },
          {2,  LevelData{1500   ,dices::D6,    0, true, {{1,1}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}} } },
          {3,  LevelData{2000   ,dices::D6,    0, true, {{1,2}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}} } },
          {4,  LevelData{6000   ,dices::D6,    0, true, {{1,2}, {2,1}, {3,0}, {4,0}, {5,0}, {6,0}} } },
          {5,  LevelData{12000  ,dices::D6,    0, true, {{1,2}, {2,2}, {3,0}, {4,0}, {5,0}, {6,0}} } },
          {6,  LevelData{24000  ,dices::D6,    0, true, {{1,2}, {2,2}, {3,1}, {4,0}, {5,0}, {6,0}} } },
          {7,  LevelData{48000  ,dices::D6,    0, true, {{1,3}, {2,2}, {3,2}, {4,0}, {5,0}, {6,0}} } },
          {8,  LevelData{90000  ,dices::D6,    0, true, {{1,3}, {2,2}, {3,2}, {4,1}, {5,0}, {6,0}} } },
          {9,  LevelData{180000 ,dices::D6,    0, true, {{1,3}, {2,3}, {3,2}, {4,2}, {5,0}, {6,0}} } },
          {10, LevelData{270000 ,dices::NoDice,1, false,{{1,3}, {2,3}, {3,2}, {4,2}, {5,1}, {6,0}} } },
          {11, LevelData{360000 ,dices::NoDice,1, false,{{1,4}, {2,3}, {3,3}, {4,2}, {5,2}, {6,0}} } },
          {12, LevelData{450000 ,dices::NoDice,1, false,{{1,4}, {2,4}, {3,3}, {4,2}, {5,2}, {6,1}} } },
          {13, LevelData{540000 ,dices::NoDice,1, false,{{1,4}, {2,4}, {3,3}, {4,3}, {5,2}, {6,2}} } },
          {14, LevelData{630000 ,dices::NoDice,1, false,{{1,4}, {2,4}, {3,4}, {4,3}, {5,2}, {6,2}} } },
          {15, LevelData{720000 ,dices::NoDice,1, false,{{1,4}, {2,4}, {3,4}, {4,3}, {5,3}, {6,2}} } },
          {16, LevelData{810000 ,dices::NoDice,1, false,{{1,5}, {2,4}, {3,4}, {4,3}, {5,3}, {6,2}} } },
          {17, LevelData{900000 ,dices::NoDice,1, false,{{1,5}, {2,5}, {3,4}, {4,3}, {5,3}, {6,2}} } },
          {18, LevelData{990000 ,dices::NoDice,1, false,{{1,5}, {2,5}, {3,4}, {4,4}, {5,3}, {6,3}} } },
          {19, LevelData{1080000,dices::NoDice,1, false,{{1,6}, {2,5}, {3,4}, {4,4}, {5,3}, {6,3}} } },
          {20, LevelData{1170000,dices::NoDice,1, false,{{1,6}, {2,5}, {3,5}, {4,4}, {5,3}, {6,3}} } },
        }
      },

      {
        CharacterClass::MagicUser,
        {
        /*LV             EXP     HitDice       HP        SPELL1 SPELL2 SPELL3 SPELL4 SPELL5 SPELL6   */
          {1,  LevelData{0      ,dices::D4,    0, true, {{1,1}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}} } },
          {2,  LevelData{2500   ,dices::D4,    0, true, {{1,2}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}} } },
          {3,  LevelData{5000   ,dices::D4,    0, true, {{1,2}, {2,1}, {3,0}, {4,0}, {5,0}, {6,0}} } },
          {4,  LevelData{10000  ,dices::D4,    0, true, {{1,2}, {2,2}, {3,0}, {4,0}, {5,0}, {6,0}} } },
          {5,  LevelData{20000  ,dices::D4,    0, true, {{1,2}, {2,2}, {3,1}, {4,0}, {5,0}, {6,0}} } },
          {6,  LevelData{40000  ,dices::D4,    0, true, {{1,3}, {2,2}, {3,2}, {4,0}, {5,0}, {6,0}} } },
          {7,  LevelData{80000  ,dices::D4,    0, true, {{1,3}, {2,2}, {3,2}, {4,1}, {5,0}, {6,0}} } },
          {8,  LevelData{150000 ,dices::D4,    0, true, {{1,3}, {2,3}, {3,2}, {4,2}, {5,0}, {6,0}} } },
          {9,  LevelData{300000 ,dices::D4,    0, true, {{1,3}, {2,3}, {3,2}, {4,2}, {5,1}, {6,0}} } },
          {10, LevelData{450000 ,dices::NoDice,1, false,{{1,4}, {2,3}, {3,3}, {4,2}, {5,2}, {6,0}} } },
          {11, LevelData{600000 ,dices::NoDice,1, false,{{1,4}, {2,4}, {3,3}, {4,2}, {5,2}, {6,1}} } },
          {12, LevelData{750000 ,dices::NoDice,1, false,{{1,4}, {2,4}, {3,3}, {4,3}, {5,2}, {6,2}} } },
          {13, LevelData{900000 ,dices::NoDice,1, false,{{1,4}, {2,4}, {3,4}, {4,3}, {5,2}, {6,2}} } },
          {14, LevelData{1050000,dices::NoDice,1, false,{{1,4}, {2,4}, {3,4}, {4,3}, {5,3}, {6,2}} } },
          {15, LevelData{1200000,dices::NoDice,1, false,{{1,5}, {2,4}, {3,4}, {4,3}, {5,3}, {6,2}} } },
          {16, LevelData{1350000,dices::NoDice,1, false,{{1,5}, {2,5}, {3,4}, {4,3}, {5,3}, {6,2}} } },
          {17, LevelData{1500000,dices::NoDice,1, false,{{1,5}, {2,5}, {3,4}, {4,4}, {5,3}, {6,3}} } },
          {18, LevelData{1650000,dices::NoDice,1, false,{{1,6}, {2,5}, {3,4}, {4,4}, {5,3}, {6,3}} } },
          {19, LevelData{1800000,dices::NoDice,1, false,{{1,6}, {2,5}, {3,5}, {4,4}, {5,3}, {6,3}} } },
          {20, LevelData{1950000,dices::NoDice,1, false,{{1,6}, {2,5}, {3,5}, {4,4}, {5,4}, {6,3}} } },
        }
      }
    }
  };

}

}

#endif // EXPERIENCE_TABLE_H
