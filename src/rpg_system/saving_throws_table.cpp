#include "saving_throws_table.h"

namespace amarlon
{

namespace SavingThrows
{

int get(Type type, CharacterClassType charClass, int level)
{
  return stTable[charClass][type][level];
}

}

}

