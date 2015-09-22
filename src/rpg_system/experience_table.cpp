#include "experience_table.h"

namespace amarlon
{

namespace Experience
{

  LevelData getLevelData(CharacterClass charClass, int level)
  {
    return expData[charClass][level];
  }

}

}

