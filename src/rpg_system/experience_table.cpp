#include "experience_table.h"

namespace amarlon
{

namespace experience_table
{

  LevelData getLevelData(CharacterClass charClass, int level)
  {
    return expData[charClass][level];
  }

}

}
