#ifndef ATTACK_BONUS_TABLE_H
#define ATTACK_BONUS_TABLE_H

#include <map>
#include <character_class_type.h>

namespace amarlon
{

namespace AttackBonus
{

  int get(CharacterClassType charClass, int level);

  static std::map< CharacterClassType, std::map<int, int> > abTable =
  {
    {
      CharacterClassType::Fighter,
      {
      /* Level, AB */
        {0,     0},
        {1,     1},
        {2,     2},
        {3,     2},
        {4,     3},
        {5,     4},
        {6,     4},
        {7,     5},
        {8,     6},
        {9,     6},
        {10,    6},
        {11,    7},
        {12,    7},
        {13,    8},
        {14,    8},
        {15,    8},
        {16,    9},
        {17,    9},
        {18,    10},
        {19,    10},
        {20,    10}
      }
    },

    {
      CharacterClassType::Cleric,
      {
      /* Level, AB */
        {0,     0},
        {1,     1},
        {2,     1},
        {3,     2},
        {4,     2},
        {5,     3},
        {6,     3},
        {7,     4},
        {8,     4},
        {9,     5},
        {10,    5},
        {11,    5},
        {12,    6},
        {13,    6},
        {14,    6},
        {15,    7},
        {16,    7},
        {17,    7},
        {18,    8},
        {19,    8},
        {20,    8}
      }
    },

    {
      CharacterClassType::Thief,
      {
      /* Level, AB */
        {0,     0},
        {1,     1},
        {2,     1},
        {3,     2},
        {4,     2},
        {5,     3},
        {6,     3},
        {7,     4},
        {8,     4},
        {9,     5},
        {10,    5},
        {11,    5},
        {12,    6},
        {13,    6},
        {14,    6},
        {15,    7},
        {16,    7},
        {17,    7},
        {18,    8},
        {19,    8},
        {20,    8}
      }
    },

    {
      CharacterClassType::MagicUser,
      {
      /* Level, AB */
        {0,     0},
        {1,     1},
        {2,     1},
        {3,     1},
        {4,     2},
        {5,     2},
        {6,     3},
        {7,     3},
        {8,     3},
        {9,     4},
        {10,    4},
        {11,    4},
        {12,    4},
        {13,    5},
        {14,    5},
        {15,    5},
        {16,    6},
        {17,    6},
        {18,    6},
        {19,    7},
        {20,    7}
      }
    },

    {
      CharacterClassType::Monster,
      {
      /* Level, AB */
        {0,      0},
        {1,      1},
        {2,      2},
        {3,      3},
        {4,      4},
        {5,      5},
        {6,      6},
        {7,      7},
        {8,      8},
        {9,      8},
        {10,     9},
        {11,     9},
        {12,     10},
        {13,     10},
        {14,     11},
        {15,     11},
        {16,     12},
        {17,     12},
        {18,     12},
        {19,     12},
        {20,     13},
        {21,     13},
        {22,     13},
        {23,     13},
        {24,     14},
        {25,     14},
        {26,     14},
        {27,     14},
        {28,     15},
        {29,     15},
        {30,     15},
        {31,     15},
        {32,     16}
      }
    }
  };

}

}
#endif // ATTACK_BONUS_TABLE_H
