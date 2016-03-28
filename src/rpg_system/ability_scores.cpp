#include "ability_scores.h"

namespace amarlon { namespace AbilityScore {

  int getModifier(int abilityScoreValue)
  {
    int mod = 0;

    if ( abilityScoreValue >= MIN_VALUE && abilityScoreValue <= MAX_VALUE )
    {
      mod = modifiersMap[ abilityScoreValue ];
    }

    return mod;
  }

  int getAbilityRollTarget(int level)
  {
    int t = 0;

    if ( level >= 1 && level <= 20 )
    {
      t = abilityRollTable[ level ];
    }

    return t;
  }

}}

