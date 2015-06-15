#include "saving_throws_table.h"

namespace amarlon
{

namespace saving_throws_table
{

int getSavingThrow(Type type, CharacterClass charClass, int level)
{
  return stTable[charClass][type][level];
}

}

}
