#include "experience_table.h"

namespace amarlon
{

namespace Experience
{

  LevelData getLevelData(CharacterClassType charClass, int level)
  {
    return expData[charClass][level];
  }

}

}

