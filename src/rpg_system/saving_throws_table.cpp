#include "saving_throws_table.h"

namespace amarlon
{

namespace SavingThrows
{

int get(Type type, CharacterClass charClass, int level)
{
  return stTable[charClass][type][level];
}

}

}

